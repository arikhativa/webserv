
#include <CgiManager/CgiManager.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

CgiManager::CgiManager(const BasicHTTPRequest &basicHTTPRequest, const Path &pathCGI, const std::string &serverName,
					   const std::string &port)
	: _basicHTTPRequest(basicHTTPRequest)
	, _pathCGI(pathCGI)
	, _serverName(serverName)
	, _port(port)
{
}

CgiManager::CgiManager(const CgiManager &src)
	: _basicHTTPRequest(src.getBasicHTTPRequest())
	, _pathCGI(src.getPathCGI())
	, _serverName(src.getServerName())
	, _port(src.getPort())
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
	  << "]";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

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

char **CgiManager::_setEnv(const std::string &bodyRequest) const
{
	std::map<std::string, std::string> env;
	env[httpConstants::CONTENT_LENGTH] = bodyRequest.length();
	if (_basicHTTPRequest.getHeaders().find(httpConstants::CONTENT_TYPE_FIELD) != _basicHTTPRequest.getHeaders().end())
		env[httpConstants::CONTENT_TYPE_FIELD] = _basicHTTPRequest.getHeaders().at(httpConstants::CONTENT_TYPE_FIELD);
	env[httpConstants::REQUEST_METHOD] = _basicHTTPRequest.getType();
	env[httpConstants::SCRIPT_FILENAME] = _pathCGI.get();
	if (_basicHTTPRequest.getQuery().length() > 1)
		env[httpConstants::QUERY_STRING] = _basicHTTPRequest.getQuery().substr(1);
	env[httpConstants::SERVER_PROTOCOL] = _basicHTTPRequest.getHTTPVersion();
	env[httpConstants::SERVER_PORT] = _port;
	env[httpConstants::SERVER_NAME] = _serverName;
	env[httpConstants::PATH_INFO] = _basicHTTPRequest.getPath();

	char **ch_env = (char **)calloc(sizeof(char *), env.size() + 1);
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

std::string CgiManager::_createpipe(char **ch_env, char **argv, const std::string &bodyRequest)
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
		write(_inputPipe[1], bodyRequest.c_str(), bodyRequest.size());
		close(_inputPipe[1]);

		char buffer[40000 * 2];
		size_t bytes_read = 0;
		std::string output;
		waitpid(pid, &_exit_status, 0);
		std::size_t pos;
		int contentLenght;
		while ((bytes_read = read(_outputPipe[0], buffer, sizeof(buffer))) > 0)
		{
			output.append(buffer, bytes_read);
			if ((pos = output.find(httpConstants::CONTENT_LENGHT_FIELD_KEY)) != std::string::npos)
			{
				std::string content_length = output.substr(pos + httpConstants::CONTENT_LENGHT_FIELD_KEY.length());
				if ((pos = content_length.find(httpConstants::FIELD_BREAK)) != std::string::npos)
					contentLenght = converter::stringToInt(content_length.substr(0, pos));
				pos = output.find(httpConstants::HEADER_BREAK);
				if ((pos != std::string::npos) &&
					output.substr(pos + httpConstants::HEADER_BREAK.length()).length() >= (size_t)contentLenght)
				{
					output = output.substr(0, pos + httpConstants::HEADER_BREAK.length() + contentLenght);
					break;
				}
			}
		}
		_free_argv_env(argv, ch_env);
		return (output);
	}
	return ("");
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

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

const std::string CgiManager::setCgiManager(const Path &pathServer, const std::string &body)
{
	char **ch_env = NULL;
	char **argv = NULL;
	std::string content = "";
	try
	{
		ch_env = _setEnv(body);
		argv = (char **)calloc(sizeof(char *), 3);
		if (!argv)
			throw CgiManager::CgiManagerException();
		argv[0] = strdup(_pathCGI.get().c_str());
		std::string path = pathServer.get() + _basicHTTPRequest.getPath();
		argv[1] = strdup(path.c_str());
		argv[2] = NULL;
		content = _createpipe(ch_env, argv, body);
	}
	catch (CgiManager::CgiManagerException &e)
	{
		_free_argv_env(argv, ch_env);
		throw CgiManager::CgiManagerException();
	}
	return (content);
}

/* ************************************************************************** */
