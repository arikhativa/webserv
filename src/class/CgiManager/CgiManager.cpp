
#include <CgiManager/CgiManager.hpp>
#include <Poll/Poll.hpp>

const int CgiManager::ERROR(0);
const int CgiManager::CHILD(0);
const int CgiManager::BUFFER_SIZE(8192);

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
CgiManager::CgiManager(const BasicHTTPRequest &basicHTTPRequest, const Path &pathCGI, const Path &local_path,
					   const std::string &serverName, const std::string &port)
	: _basicHTTPRequest(basicHTTPRequest)
	, _pathCGI(pathCGI)
	, _local_path(local_path)
	, _serverName(serverName)
	, _port(port)
	, _byte_write(0)
	, _byte_read(0)
{
}

const char *CgiManager::CgiManagerException::what() const throw()
{
	return "Error in CgiManager";
}

const char *CgiManager::CgiManagerIncompleteRead::what() const throw()
{
	return "Read is not completed";
}

const char *CgiManager::CgiManagerIncompleteWrite::what() const throw()
{
	return "Write is not completed";
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

	std::map< std::string, std::string >::const_iterator cit =
		_basicHTTPRequest.getHeaders().find(httpConstants::headers::CONTENT_LENGTH);

	if (cit != _basicHTTPRequest.getHeaders().end())
		env[httpConstants::cgi::CONTENT_LENGTH] = cit->second;

	cit = _basicHTTPRequest.getHeaders().find(httpConstants::headers::CONTENT_TYPE);
	if (cit != _basicHTTPRequest.getHeaders().end())
		env[httpConstants::cgi::CONTENT_TYPE] = cit->second;

	env[httpConstants::cgi::REQUEST_METHOD] = BasicHTTPRequest::toStringType(_basicHTTPRequest.getType());
	env[httpConstants::cgi::SCRIPT_FILENAME] = _pathCGI.get();
	if (_basicHTTPRequest.getQuery().length() > 1)
		env[httpConstants::cgi::QUERY_STRING] = _basicHTTPRequest.getQuery().substr(1);
	env[httpConstants::cgi::SERVER_PROTOCOL] = ABaseHTTPCall::toStringVersion(_basicHTTPRequest.getHTTPVersion());
	env[httpConstants::cgi::SERVER_PORT] = _port;
	env[httpConstants::cgi::SERVER_NAME] = _serverName;
	env[httpConstants::cgi::PATH_INFO] = _basicHTTPRequest.getPath();
	env[httpConstants::cgi::SCRIPT_NAME] = _basicHTTPRequest.getPath();
	env[httpConstants::cgi::SERVER_SOFTWARE] = httpConstants::SERVER_FIELD_VALUE;

	std::map< std::string, std::string >::const_iterator it = env.begin();
	for (int i = 0; it != env.end(); it++, i++)
		_env.add(it->first + "=" + it->second);
}

void CgiManager::_setArgv(void)
{
	_argv.add(_pathCGI.get());
	_argv.add(_local_path.get());
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
	dup2(STDOUT_FILENO, STDERR_FILENO);
	_exit_status = execve(_argv.toCTable()[0], _argv.toCTable(), _env.toCTable());
	if (_exit_status < 0)
		throw CgiManager::CgiManagerException();
	exit(_exit_status);
}

void CgiManager::writeToCgi(void)
{
	if (_byte_write > _basicHTTPRequest.getBody().size())
		throw CgiManager::CgiManagerException();

	const char *buff = &(_basicHTTPRequest.getBody()[_byte_write]);
	::size_t size = _basicHTTPRequest.getBody().size() - _byte_write;

	int byte_write = write(this->getWriteFd(), buff, size);
	this->_byte_write += byte_write;

	if (this->_byte_write >= this->_basicHTTPRequest.getBody().size())
		return;
	if (byte_write > 0)
		throw CgiManager::CgiManagerIncompleteWrite();
	if (byte_write == -1)
		throw CgiManager::CgiManagerException();
}

void CgiManager::readFromCgi(void)
{
	int bytes_read = 0;
	char buffer[BUFFER_SIZE];
	std::size_t pos;
	int contentLenght;

	bytes_read = read(this->getReadFd(), buffer, sizeof(buffer));
	if (bytes_read <= -1)
		throw CgiManagerException();
	if (bytes_read > 0)
	{
		_output.append(buffer, bytes_read);
		if ((pos = _output.find(httpConstants::CONTENT_LENGHT_FIELD_KEY)) != std::string::npos)
		{
			std::string content_length = _output.substr(pos + httpConstants::CONTENT_LENGHT_FIELD_KEY.length());
			if ((pos = content_length.find(httpConstants::FIELD_BREAK)) != std::string::npos)
				contentLenght = converter::stringToInt(content_length.substr(0, pos));
			pos = _output.find(httpConstants::HEADER_BREAK);
			if ((pos != std::string::npos) &&
				_output.substr(pos + httpConstants::HEADER_BREAK.length()).length() >= (size_t)contentLenght)
			{
				_output = _output.substr(0, pos + httpConstants::HEADER_BREAK.length() + contentLenght);
				return;
			}
		}
		if (bytes_read < BUFFER_SIZE)
			return;
		throw CgiManagerIncompleteRead();
	}
}

void CgiManager::closePipe(void)
{
	this->_pipe.closeInput();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string CgiManager::getOutput(void) const
{
	return this->_output;
}

int CgiManager::getWriteFd(void) const
{
	return this->_pipe.getInput();
}

int CgiManager::getReadFd(void) const
{
	return this->_pipe.getOutput();
}

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

void CgiManager::writeToPipe(const std::string &str) const
{
	_pipe.write(str);
}

int CgiManager::getPid(void) const
{
	return this->_pid;
}

int CgiManager::getBytesWrite(void) const
{
	return this->_byte_write;
}

int CgiManager::getBytesRead(void) const
{
	return this->_byte_read;
}

void CgiManager::executeCgiManager(void)
{
	std::string content = "";
	_pipe.initPipe();
	_setEnv();
	_setArgv();
	this->_pid = _createFork();
	if (this->_pid == CHILD)
		_childProcess();
	else
		_pipe.setParent();
}

/* ************************************************************************** */
