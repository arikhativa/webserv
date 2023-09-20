
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
	_env = Tab();
	_argv = Tab();
	_pipe = Pipe();
	_basicHTTPRequest.parseRaw();
	if (_basicHTTPRequest.isBody())
		_basicHTTPRequest.parseBody();
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

void CgiManager::_setEnv(void)
{
	std::map< std::string, std::string > env;
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

	std::map< std::string, std::string >::const_iterator it = env.begin();
	for (int i = 0; it != env.end(); it++, i++)
		_env.add(it->first + "=" + it->second);
}

void CgiManager::_setArgv(const Path &pathServer)
{
	_argv.add(_pathCGI.get());
	_argv.add(pathServer.get() + _basicHTTPRequest.getPath());
}

int CgiManager::_createFork(void)
{
	int pid = fork();
	if (pid < ERROR)
		throw CgiManager::CgiManagerException();
	return (pid);
}

void CgiManager::_childProcess(void)
{
	int _exit_status;
	_pipe.setChild();
	_exit_status = execve(_argv.toCTable()[0], _argv.toCTable(), _env.toCTable());
	if (_exit_status < 0)
		throw CgiManager::CgiManagerException();
	exit(_exit_status);
}

std::string CgiManager::_parentProcess(int pid)
{
	_pipe.setParent();
	if (_basicHTTPRequest.isBody())
		_pipe.write(_basicHTTPRequest.getBody());
	_pipe.closeInput();
	return (_readCgiOutput(pid));
}

std::string CgiManager::_readCgiOutput(int pid)
{
	std::string output = "";
	size_t bytes_read = 0;
	char buffer[BUFFER_SIZE];
	std::size_t pos;
	int contentLenght;
	waitpid(pid, NULL, 0);
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
	return (output);
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

const std::string CgiManager::executeCgiManager(const Path &pathServer)
{
	std::string content = "";
	_setEnv();
	_setArgv(pathServer);
	int pid = _createFork();
	if (pid == CHILD)
		_childProcess();
	else
		content = _parentProcess(pid);
	return (content);
}

/* ************************************************************************** */
