
#include <CgiManager/CgiManager.hpp>

const int CgiManager::ERROR(0);
const int CgiManager::CHILD(0);
const int CgiManager::BUFFER_SIZE(8192);

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
	_env = NULL;
	_pipe = Pipe();
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

void CgiManager::_freeTable(char **var)
{
	if (var != NULL)
	{
		for (int i = 0; var[i] != NULL; i++)
		{
			if (var[i] != NULL)
				free(var[i]);
			var[i] = NULL;
		}
		free(var);
		var = NULL;
	}
}

void CgiManager::_setEnv(void)
{
	std::map<std::string, std::string> env;
	if (_basicHTTPRequest.getHeaders().find(httpConstants::CONTENT_LENGTH) != _basicHTTPRequest.getHeaders().end())
		env[httpConstants::CONTENT_LENGTH] = _basicHTTPRequest.getHeaders().at(httpConstants::CONTENT_LENGTH);
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
	if (_env != NULL)
		_freeTable(_env);
	_env = (char **)calloc(sizeof(char *), env.size() + 1);
	if (!_env)
		throw CgiManager::CgiManagerException();
	std::map<std::string, std::string>::const_iterator it = env.begin();
	for (int i = 0; it != env.end(); it++, i++)
	{
		std::string tmp = it->first + "=" + it->second;
		_env[i] = strdup(tmp.c_str());
	}
	_env[env.size()] = NULL;
}

const std::string CgiManager::_createpipe(char **argv)
{
	int _exit_status;

	int pid = fork();
	if (pid < ERROR)
		throw CgiManager::CgiManagerException();
	if (pid == CHILD)
	{
		_pipe.setChild();
		_exit_status = execve(argv[0], argv, getCEnv());
		if (_exit_status < 0)
			throw CgiManager::CgiManagerException();
		exit(_exit_status);
	}
	else
	{
		_pipe.setParent();
		if (_basicHTTPRequest.getBody() != "")
			_pipe.write(_basicHTTPRequest.getBody());
		_pipe.closeInput();

		char buffer[BUFFER_SIZE];
		size_t bytes_read = 0;
		std::string output;
		waitpid(pid, &_exit_status, 0);
		std::size_t pos;
		int contentLenght;
		while ((bytes_read = read(_pipe.getOutput(), buffer, sizeof(buffer))) > 0)
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
		_freeTable(_env);
		_freeTable(argv);
		return (output);
	}
	return ("");
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

Path CgiManager::getPathCGI(void) const
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

BasicHTTPRequest CgiManager::getBasicHTTPRequest(void) const
{
	return this->_basicHTTPRequest;
}

char **CgiManager::getCEnv(void) const
{
	return this->_env;
}

const std::string CgiManager::setCgiManager(const Path &pathServer)
{
	char **argv = NULL;
	std::string content = "";
	try
	{
		_setEnv();
		argv = (char **)calloc(sizeof(char *), 3);
		if (!argv)
			throw CgiManager::CgiManagerException();
		argv[0] = strdup(_pathCGI.get().c_str());
		std::string path = pathServer.get() + _basicHTTPRequest.getPath();
		argv[1] = strdup(path.c_str());
		argv[2] = NULL;
		content = _createpipe(argv);
	}
	catch (CgiManager::CgiManagerException &e)
	{
		_freeTable(argv);
		_freeTable(_env);
		throw CgiManager::CgiManagerException();
	}
	return (content);
}

/* ************************************************************************** */
