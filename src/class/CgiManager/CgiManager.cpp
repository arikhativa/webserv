
#include <CgiManager/CgiManager.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/


CgiManager::CgiManager(const BasicHTTPRequest &basicHTTPRequest, const Path &pathCGI, const std::string &serverName,const std::string &port)
	: _basicHTTPRequest(basicHTTPRequest), _pathCGI(pathCGI), _serverName(serverName), _port(port)
{
}


CgiManager::CgiManager(const CgiManager &src)
	: _basicHTTPRequest(src.getBasicHTTPRequest()), _pathCGI(src.getPathCGI()), _serverName(src.getServerName()), _port(src.getPort())
{
}

const char *CgiManager::CgiManagerException::what() const throw()
{
	return "Error in CgiManager";
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

CgiManager::~CgiManager()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

CgiManager &CgiManager::operator=(CgiManager const &rhs)
{
	if (this != &rhs)
	{
		this->_pathCGI = rhs.getPathCGI();
		this->_serverName = rhs.getServerName();
		this->_port = rhs.getPort();
		this->_basicHTTPRequest = rhs.getBasicHTTPRequest();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, CgiManager const &i)
{
	o << "CgiManager[ ServerName=\"" << i.getServerName() << "\""
	<< "Port=\"" << i.getPort() << "\""
	<< "PathCGI=\"" << i.getPathCGI() << "\""
	<< "BasicHTTPRequest=\"" << i.getBasicHTTPRequest() << "\""
	<<	 "]";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

void CgiManager::setPathCGI(const Path &pathCGI)
{
	this->_pathCGI = pathCGI;
}

void CgiManager::setServerName(const std::string &serverName)
{
	this->_serverName = serverName;
}

void CgiManager::setPort(const std::string &port)
{
	this->_port = port;
}

void CgiManager::setBasicHTTPRequest(const BasicHTTPRequest &basicHTTPRequest)
{
	this->_basicHTTPRequest = basicHTTPRequest;
}

const Path CgiManager::getPathCGI(void) const
{
	return this->_pathCGI;
}

const std::string CgiManager::getServerName(void) const
{
	return this->_serverName;
}

const std::string CgiManager::getPort(void) const
{
	return this->_port;
}

const BasicHTTPRequest CgiManager::getBasicHTTPRequest(void) const
{
	return this->_basicHTTPRequest;
}

char **CgiManager::_setEnv(void) const
{
	std::map<std::string, std::string> env;
	//TODO -> env["CONTENT_LENGTH"] = _basicHTTPRequest.getBody().length();
	std::string bodyRequest = "this is a test";
	env["CONTENT_LENGTH"] = bodyRequest.size();
	if (_basicHTTPRequest.getHeaders().find(httpConstants::CONTENT_TYPE_FIELD) != _basicHTTPRequest.getHeaders().end())
		env[httpConstants::CONTENT_TYPE_FIELD] = _basicHTTPRequest.getHeaders().at(httpConstants::CONTENT_TYPE_FIELD);
	env[httpConstants::REQUEST_METHOD] = _basicHTTPRequest.getType();
	env[httpConstants::SCRIPT_FILENAME] = _pathCGI.get();
	if (_basicHTTPRequest.getQuery().length() > 1)
		env[httpConstants::QUERY_STRING] = _basicHTTPRequest.getQuery().substr(1);
	env[httpConstants::SERVER_PROTOCOL] = _basicHTTPRequest.getHTTPVersion();
	env[httpConstants::SERVER_PORT] = _port;
	env[httpConstants::SERVER_NAME] = _serverName;


	char	**ch_env = (char **)calloc(sizeof(char *), env.size() + 1);
	if (!ch_env)
		throw CgiManager::CgiManagerException();
	std::map<std::string, std::string>::const_iterator it = env.begin();
	for (int i = 0; it != env.end(); it++, i++)
	{
		std::string tmp = it->first + "=" + it->second;
		ch_env[i] = strdup(tmp.c_str());
	}
	ch_env[env.size()] = NULL;
	return (ch_env);
}

std::string CgiManager::_createpipe(char **ch_env, char **argv)
{
	int _exit_status;
	if (pipe(_inputPipe) < 0 || pipe(_outputPipe) < 0)
		throw CgiManager::CgiManagerException();
	int pid = fork();
	if (pid < 0)
		throw CgiManager::CgiManagerException();
	if (pid == 0)
	{
		dup2(_inputPipe[0], STDIN_FILENO);
		dup2(_outputPipe[1], STDOUT_FILENO);
		close(_inputPipe[0]);
		close(_inputPipe[1]);
		close(_outputPipe[0]);
		close(_outputPipe[1]);
		_exit_status = execve(argv[0], argv, ch_env);
		exit(_exit_status);
	}
	else if (pid > 0)
	{
		close(_inputPipe[0]);
		close(_outputPipe[1]);
		//TODO -> write(_inputPipe[1], _basicHTTPRequest.getBody().c_str(), _basicHTTPRequest.getBody().length());
		std::string bodyRequest = "this is a test";
		write(_inputPipe[1], bodyRequest.c_str(), bodyRequest.size());
		
		close(_inputPipe[1]);

		char buffer[40000 * 2];
		size_t bytes_read = 0;
		std::string output;
		waitpid(pid, &_exit_status, 0);
		while ((bytes_read = read(_outputPipe[0], buffer, sizeof(buffer))) > 0)
		{
			output.append(buffer, bytes_read);
			if (output.find("Content-Length: ") != std::string::npos)
			{
				std::size_t pos = output.find("Content-Length: ");
				std::string content_length = output.substr(pos + 16);
				pos = content_length.find(httpConstants::FIELD_BREAK);
				if (pos != std::string::npos)
					content_length = content_length.substr(0, pos);
				std::stringstream ss;
				ss << content_length;
				size_t size_int;
				ss >> size_int;
				if (size_int == output.length() - pos - 2)
					break;
			}
		}
		_free_argv_env(argv, ch_env);
		return (output);
	}
	return ("");
}

void CgiManager::_free_argv_env(char **ch_env, char **argv) 
{
	if (argv != NULL)
	{
		for (int i = 0; argv[i] != NULL; i++)
		{
			if (argv[i] != NULL)
				free(argv[i]);
			argv[i] = NULL;
		}
		free(argv);
		argv = NULL;
	}
	if (ch_env != NULL)
	{
		for (int i = 0; ch_env[i] != NULL; i++)
		{
			if (ch_env[i] != NULL)
				free(ch_env[i]);
			ch_env[i] = NULL;
		}
		free(ch_env);
		ch_env = NULL;
	}
}

const std::string CgiManager::setCgiManager(void) 
{
	char		**ch_env = NULL;
	char		**argv = NULL;
	std::string	content = "";
	try
	{
		ch_env = _setEnv();
		argv = (char **)calloc(sizeof(char *), 3);
		if (!argv)
			throw CgiManager::CgiManagerException();
		argv[0] = strdup(_pathCGI.get().c_str());
		std::string path = "." + _basicHTTPRequest.getPath();
		argv[1] = strdup(path.c_str());
		argv[2] = NULL;
		content = _createpipe(ch_env, argv);
	}
	catch (CgiManager::CgiManagerException &e)
	{
		_free_argv_env(argv, ch_env);
		throw CgiManager::CgiManagerException();
	}
	/* //! TODO: move this to a httprequesthandler 
	std::size_t pos = content.find("Content-Type: ");
	std::string content_type = "";
	if (pos != std::string::npos)
	{
		std::size_t pos2 = content.find(httpConstants::FIELD_BREAK, pos);
		if (pos2 != std::string::npos)
		{
			content_type = content.substr(pos + 14, pos2 - pos - 14);
			response.setContentType(content_type);
		}
	}
	response.setContentType(content_type);
	pos = content.find(httpConstants::HEADER_BREAK);
	if (pos != std::string::npos)
		content = content.substr(pos + 4);*/
	return (content);
}

/* ************************************************************************** */
