
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

::size_t findCaseInsensitive(const std::string &str, const std::string &search)
{
	std::string strLower = str;
	std::string searchLower = search;

	std::transform(strLower.begin(), strLower.end(), strLower.begin(), ::tolower);
	std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);

	return strLower.find(searchLower);
}

void CgiManager::readFromCgi(void)
{
	::ssize_t bytes_read = 0;
	char buffer[BUFFER_SIZE];
	::size_t pos;

	bytes_read = read(this->getReadFd(), buffer, sizeof(buffer));

	if (bytes_read <= -1)
		throw CgiManagerException();

	_output.insert(_output.end(), buffer, buffer + bytes_read);

	if (bytes_read == BUFFER_SIZE)
		throw CgiManagerIncompleteRead();

	std::string headers_str(_output.begin(), _output.end());

	if (!header::validateHeaders(headers_str))
	{
		return;
	}

	pos = headers_str.find(httpConstants::HEADER_BREAK);
	if (pos == std::string::npos)
	{
		return;
	}

	pos = findCaseInsensitive(headers_str, httpConstants::headers::CONTENT_LENGTH);
	if (pos == std::string::npos)
	{
		return;
	}
	pos += httpConstants::headers::CONTENT_LENGTH.length() + 1;
	while (_output[pos] == ' ')
	{
		++pos;
	}
	::size_t end = headers_str.find(httpConstants::FIELD_BREAK, pos);

	::size_t content_length;
	try
	{
		content_length = converter::stringToSizeT(headers_str.substr(pos, end - pos));
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error in CGI response: invalid content length: " << e.what() << std::endl;
		return;
	}

	pos = headers_str.find(httpConstants::HEADER_BREAK);
	if (pos == std::string::npos)
	{
		return;
	}

	std::vector< char > tmp_body = vectorUtils::subvec(_output, pos + httpConstants::HEADER_BREAK.length());

	if (content_length == tmp_body.size())
	{
		return;
	}

	if (content_length > tmp_body.size())
	{
		if (bytes_read != 0)
			throw CgiManagerIncompleteRead();
	}

	if (content_length < tmp_body.size())
	{
		_output[pos + httpConstants::HEADER_BREAK.length() + content_length] = '\0';
		return;
	}
}

void CgiManager::closePipe(void)
{
	this->_pipe.closeInput();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

const std::vector< char > &CgiManager::getOutput(void) const
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
