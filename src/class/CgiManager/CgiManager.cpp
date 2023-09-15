
#include <CgiManager/CgiManager.hpp>
#include <Poll/Poll.hpp>

const int CgiManager::ERROR(0);
const int CgiManager::CHILD(0);
const int CgiManager::BUFFER_SIZE(8192);

namespace cgihandler
{
	Poll::ret_stt write(Poll &p, int fd, int revents, Poll::Param &param)
	{
		(void)p;
		(void)fd;
		(void)revents;
		(void)param;

		return Poll::DONE;
	}

	Poll::ret_stt read(Poll &p, int fd, int revents, Poll::Param &param)
	{
		(void)p;
		(void)fd;
		(void)revents;
		(void)param;

		return Poll::DONE;
	}
}; // namespace cgihandler

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
CgiManager::CgiManager(const BasicHTTPRequest &basicHTTPRequest, const Path &pathCGI, const std::string &serverName,
					   const std::string &port)
	: _basicHTTPRequest(basicHTTPRequest)
	, _pathCGI(pathCGI)
	, _serverName(serverName)
	, _port(port)
	, _byte_write(0)
	, _byte_read(0)
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

	std::map<std::string, std::string>::const_iterator it = env.begin();
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

void CgiManager::writeToCgi(void)
{
	// int byte_write = write(this->getWriteFd(), this->_basicHTTPRequest.getBody().c_str(),
	// 						   this->_basicHTTPRequest.getBody().length());
	int byte_write = send(this->getWriteFd(), this->_basicHTTPRequest.getBody().c_str(),
						  this->_basicHTTPRequest.getBody().length(), MSG_DONTWAIT);
	this->_byte_write += byte_write;
	if (this->_byte_write >= this->_basicHTTPRequest.getBody().length())
		return;
	if (byte_write > 0)
		throw CgiManager::CgiManagerIncompleteWrite();
	if (byte_write == -1)
		throw CgiManager::CgiManagerException();
}

void CgiManager::readToCgi(void)
{
	int bytes_read = 0;
	char buffer[BUFFER_SIZE];
	std::size_t pos;
	int contentLenght;
	int _exit_status;

	int ret = waitpid(this->_pid, &_exit_status, WNOHANG);

	if (!ret || ret == -1 || ret != this->_pid)
		throw CgiManagerIncompleteRead();
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
				return ;
			}
		}
		throw CgiManagerIncompleteRead();
	}
	// ResponseHeader response(HTTPStatusCode(HTTPStatusCode::OK), this->.call.getErrorPages());
	// response.setBody(_output);
	// param.call.setResponse(response.getResponse());
}

// std::string CgiManager::_parentProcess(int pid)
// {
// 	_pipe.setParent();
// 	if (_basicHTTPRequest.isBody())
// 		writeToPipe(_basicHTTPRequest.getBody());
// 	// _pipe.closeInput();
// 	return (_readCgiOutput(pid));
// }

// std::string CgiManager::_readCgiOutput(int pid)
// {
// 	size_t bytes_read = 0;
// 	char buffer[BUFFER_SIZE];
// 	std::size_t pos;
// 	int contentLenght;
// 	int _exit_status;

// 	waitpid(pid, &_exit_status, 0);
// 	while ((bytes_read = read(_pipe.getOutput(), buffer, sizeof(buffer))) > 0)
// 	{
// 		_output.append(buffer, bytes_read);
// 		if ((pos = _output.find(httpConstants::CONTENT_LENGHT_FIELD_KEY)) != std::string::npos)
// 		{
// 			std::string content_length = _output.substr(pos + httpConstants::CONTENT_LENGHT_FIELD_KEY.length());
// 			if ((pos = content_length.find(httpConstants::FIELD_BREAK)) != std::string::npos)
// 				contentLenght = converter::stringToInt(content_length.substr(0, pos));
// 			pos = _output.find(httpConstants::HEADER_BREAK);
// 			if ((pos != std::string::npos) &&
// 				_output.substr(pos + httpConstants::HEADER_BREAK.length()).length() >= (size_t)contentLenght)
// 			{
// 				_output = _output.substr(0, pos + httpConstants::HEADER_BREAK.length() + contentLenght);
// 				break;
// 			}
// 		}
// 	}
// 	return (_output);
// }

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

const std::string CgiManager::executeCgiManager(const Path &pathServer)
{
	std::string content = "";
	_setEnv();
	_setArgv(pathServer);
	this->_pid = _createFork();
	if (this->_pid == CHILD)
		_childProcess();
	else
		_pipe.setParent();
	// content = _parentProcess(pid);
	return ("");
	// return (content);
}

/* ************************************************************************** */
