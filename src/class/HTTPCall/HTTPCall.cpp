#include <HTTPCall/HTTPCall.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

const int HTTPCall::MAX_CHUNK_ATTEMPTS = 5;
const int HTTPCall::RECV_BUFFER_SIZE = 4096;

HTTPCall::HTTPCall()
	: _virtual_server(NULL)
	, _client_fd(-1)
	, _request_attempts(0)
	, _response_attempts(0)
	, _bytes_sent(0)
	, _response("")
	, _basic_request("")
{
}

HTTPCall::HTTPCall(const Server *virtual_server, int client_fd)
	: _virtual_server(virtual_server)
	, _client_fd(client_fd)
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
	return "Didn't recieve request: recv() failed";
}

const char *HTTPCall::SendingResponseEmpty::what() const throw()
{
	return "Didn't send response: send() return was 0";
}

const char *HTTPCall::ReceivingRequestEmpty::what() const throw()
{
	return "Didn't recieve request: recv() return was 0";
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
		HTTPRequestHandler::GET(*this);
		break;
	case BasicHTTPRequest::POST:
		HTTPRequestHandler::POST(*this);
		break;
	case BasicHTTPRequest::DELETE:
		HTTPRequestHandler::DELETE(*this);
		break;
	default: // Uknown request
		HTTPRequestHandler::UNKNOWN(*this);
		break;
	}
}

void HTTPCall::terminate(void)
{
	close(this->_client_fd);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

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

Socket *HTTPCall::getSocket(void) const
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

int HTTPCall::getClientFd(void) const
{
	return this->_client_fd;
}

std::list<const IErrorPage *> HTTPCall::getErrorPages(void) const
{
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

void HTTPCall::setServerConf(const IServerConf *server_conf)
{
	this->_server_conf = server_conf;
}

void HTTPCall::setLocation(const ILocation *location)
{
	this->_location = location;
}

/* ************************************************************************** */