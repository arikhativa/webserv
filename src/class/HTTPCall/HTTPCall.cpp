#include <HTTPCall/HTTPCall.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

const int HTTPCall::MAX_CHUNK_ATTEMPTS = 5;
const int HTTPCall::RECV_BUFFER_SIZE = 4096;

HTTPCall::HTTPCall(const Socket *socket, int client_fd)
	: _socket(socket)
	, _client_fd(client_fd)
	, _cgi(NULL)
	, _request_attempts(0)
	, _response_attempts(0)
	, _bytes_sent(0)
	, _response("")
	, _basic_request("")
{
}

const char *HTTPCall::SendingResponseError::what() const throw()
{
	return "Couldn't send response: send() failed";
}

const char *HTTPCall::ReceivingRequestError::what() const throw()
{
	return "Didn't receive request: recv() failed";
}

const char *HTTPCall::SendingResponseEmpty::what() const throw()
{
	return "Didn't send response: send() return was 0";
}

const char *HTTPCall::ReceivingRequestEmpty::what() const throw()
{
	return "Didn't receive request: recv() return was 0";
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

HTTPCall::~HTTPCall()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

std::ostream &operator<<(std::ostream &o, HTTPCall const &i)
{
	o << "HTTPCall[" << i.getBasicRequest() << "]";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

std::string HTTPCall::getExtension(void) const
{
	std::size_t pos = _local_path.get().find_last_of(".");
	if (pos == std::string::npos)
		return (_local_path.get());
	return (_local_path.get().substr(pos));
}

bool HTTPCall::isCGI(void) const
{
	return (this->getLocation()->getCGIConf().isSet() &&
			this->getLocation()->getCGIConf().getExtension() == this->getExtension());
}

void HTTPCall::_setLocalPath(void)
{
	const BasicHTTPRequest &req(getBasicRequest());
	const IPath *root = getLocation()->getRoot();

	Path local_path(root->get() + req.getPath());
	if (FileManager::isFileExists(local_path.get()))
	{
		_local_path = local_path;
		return;
	}

	if (local_path.isDir())
	{
		std::string tmp;
		const std::list< std::string > &list = getLocation()->getIndexFiles();
		for (std::list< std::string >::const_iterator it = list.begin(); it != list.end(); ++it)
		{
			tmp = local_path.get() + *it;
			if (FileManager::isFileExists(tmp))
			{
				_local_path.set(tmp);
				return;
			}
		}
	}
	_local_path = local_path;
}

bool HTTPCall::_isMethodAllowed(void)
{
	const IAllowedMethods &am(getLocation()->getAllowedMethods());
	IAllowedMethods::type t = static_cast< IAllowedMethods::type >(getBasicRequest().getType());
	return am.isAllowed(t);
}

bool HTTPCall::_isBodySizeAllowed(void)
{
	size_t max(getLocation()->getMaxBodySize());

	if (!max)
		return true;

	if (getBasicRequest().isBody())
		return max >= getBasicRequest().getBody().size();
	return true;
}

bool HTTPCall::_isUploadAllowed(void)
{
	if (!getLocation()->canUpload())
	{
		return !getBasicRequest().isUploadFile();
	}
	return true;
}

bool HTTPCall::isRequestAllowed(void)
{
	HTTPStatusCode stt(HTTPStatusCode::ACCEPTED);

	if (!_isMethodAllowed())
	{
		stt = HTTPStatusCode::FORBIDDEN;
	}
	else if (!_isBodySizeAllowed())
	{
		stt = HTTPStatusCode::REQUEST_ENTITY_TOO_LARGE;
	}
	else if (!_isUploadAllowed())
	{
		stt = HTTPStatusCode::FORBIDDEN;
	}

	if (stt != HTTPStatusCode::ACCEPTED)
	{
		ResponseHeader response(stt, getLocation()->getErrorPageSet());
		setResponse(response.getResponse());
		return false;
	}

	return true;
}

void HTTPCall::finalizeRequest(void)
{
	_setLocalPath();
}

void HTTPCall::recvRequest(void)
{
	int tmp_recv_len;
	char tmp_raw[HTTPCall::RECV_BUFFER_SIZE];

	tmp_recv_len = recv(this->_client_fd, tmp_raw, sizeof(tmp_raw), MSG_DONTWAIT);
	if (tmp_recv_len <= -1)
		throw ReceivingRequestError();
	if (tmp_recv_len == 0)
		throw ReceivingRequestEmpty();
	this->_request_attempts++;
	this->_basic_request.extenedRaw(tmp_raw);
}

void HTTPCall::sendResponse(void)
{
	int send_status;
	send_status = send(this->_client_fd, this->_response.c_str(), this->_response.size(), MSG_DONTWAIT);
	if (send_status <= -1)
		throw SendingResponseError();
	if (send_status == 0)
		throw SendingResponseEmpty();
	this->_response_attempts++;
	this->_bytes_sent += send_status;
}

void HTTPCall::handleRequest(void)
{
	switch (this->_basic_request.getType())
	{
	case BasicHTTPRequest::GET:
		if (this->isCGI())
			HTTPRequestHandler::CGI(*this);
		else
			HTTPRequestHandler::GET(*this);
		break;
	case BasicHTTPRequest::POST:
		if (this->isCGI())
			HTTPRequestHandler::CGI(*this);
		else
			HTTPRequestHandler::POST(*this);
		break;
	case BasicHTTPRequest::DELETE:
		HTTPRequestHandler::DELETE(*this);
		break;
	default:
		HTTPRequestHandler::UNKNOWN(*this);
		break;
	}
}

void HTTPCall::terminate(void)
{
	close(this->_client_fd);
}

void HTTPCall::cgiToResponse(void)
{
	ResponseHeader response(HTTPStatusCode(HTTPStatusCode::OK), this->getLocation()->getErrorPageSet());
	if (this->_cgi->getOutput().find(httpConstants::HEADER_BREAK) == std::string::npos)
	{
		response.setBody(this->_cgi->getOutput());
		this->setResponse(response.getResponse());
		return;
	}

	std::map< std::string, std::string > _headers;
	std::size_t start = 0;
	std::size_t end = this->_cgi->getOutput().find(httpConstants::FIELD_BREAK, start);

	if (end == std::string::npos)
		throw ABaseHTTPCall::Incomplete("Bad header: missing end of the first header");
	while (end != std::string::npos && end <= this->_cgi->getOutput().find(httpConstants::HEADER_BREAK) && start != end)
	{
		std::size_t colon_pos = this->_cgi->getOutput().find(":", start);
		if (colon_pos > end)
			throw ABaseHTTPCall::Invalid("Bad header: missing colon");

		std::string key = converter::toNginxStyle(this->_cgi->getOutput().substr(start, colon_pos - start));

		colon_pos += 2;
		std::string value = this->_cgi->getOutput().substr(colon_pos, end - colon_pos);
		if (ABaseHTTPCall::isKeyRestricted(key) && !_headers[key].empty())
			throw ABaseHTTPCall::Invalid("Bad header: duplicate restricted key: " + key);
		if (_headers[key].empty())
			_headers[key] = value;
		else
			_headers[key] += ", " + value;
		start = end + 2;
		end = this->_cgi->getOutput().find(httpConstants::FIELD_BREAK, start);
	}
	for (std::map< std::string, std::string >::const_iterator it = _headers.begin(); it != _headers.end(); ++it)
	{
		response.setHeader(it->first, it->second);
	}
	response.setBody(this->_cgi->getOutput().substr(this->_cgi->getOutput().find(httpConstants::HEADER_BREAK) +
													httpConstants::HEADER_BREAK.length() + 1));
	this->setResponse(response.getResponse());
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

CgiManager *HTTPCall::getCgi(void) const
{
	return this->_cgi;
}

int HTTPCall::getRequestAttempts(void) const
{
	return this->_request_attempts;
}

int HTTPCall::getResponseAttempts(void) const
{
	return this->_response_attempts;
}

long unsigned int HTTPCall::getBytesSent(void) const
{
	return this->_bytes_sent;
}

const Socket *HTTPCall::getSocket(void) const
{
	return this->_socket;
}

BasicHTTPRequest &HTTPCall::getBasicRequest(void)
{
	return this->_basic_request;
}

const BasicHTTPRequest &HTTPCall::getBasicRequest(void) const
{
	return this->_basic_request;
}

std::string HTTPCall::getResponse(void) const
{
	return this->_response;
}

std::string HTTPCall::getClientHostHeader(void) const
{
	return this->_basic_request.getHost();
}

int HTTPCall::getClientFd(void) const
{
	return this->_client_fd;
}

std::list< const IErrorPage * > HTTPCall::getErrorPages(void) const
{
	if (this->_server_conf == NULL)
		return std::list< const IErrorPage * >();
	return this->_server_conf->getErrorPages();
}

void HTTPCall::setBasicRequest(const BasicHTTPRequest &request)
{
	this->_basic_request = request;
}

void HTTPCall::setResponse(const std::string &response)
{
	this->_response = response;
}

void HTTPCall::setClientFd(int fd)
{
	this->_client_fd = fd;
}

void HTTPCall::parseRawRequest(void)
{
	this->_basic_request.parseBody();
}
const IServerConf *HTTPCall::getServerConf(void) const
{
	return this->_server_conf;
}

const ILocation *HTTPCall::getLocation(void) const
{
	return this->_location;
}

const Path &HTTPCall::getLocalPath(void) const
{
	return this->_local_path;
}

void HTTPCall::setServerConf(const IServerConf *server_conf)
{
	this->_server_conf = server_conf;
}

void HTTPCall::setLocation(const ILocation *location)
{
	this->_location = location;
}

void HTTPCall::setCgi(CgiManager *cgi)
{
	this->_cgi = cgi;
}

/* ************************************************************************** */