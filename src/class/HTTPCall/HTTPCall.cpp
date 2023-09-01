#include <HTTPCall/HTTPCall.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

const unsigned int HTTPCall::MAX_CHUNK_ATTEMPTS = 5;
const unsigned int HTTPCall::RECV_BUFFER_SIZE = 4096;

HTTPCall::HTTPCall(Server *virtualServer, int clientFd)
	: _virtual_server(virtualServer)
	, _client_fd(clientFd)
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

const char *HTTPCall::RecievingRequestError::what() const throw()
{
	return "Didn't recieve request: recv() failed";
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
	o << "HTTPRequest[" << i.getBasicRequest() << "]";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void HTTPCall::recvRequest(void)
{
	int tmpRecvLen;
	char tmpRaw[HTTPCall::RECV_BUFFER_SIZE];

	tmpRecvLen = recv(this->_client_fd, tmpRaw, sizeof(tmpRaw), MSG_DONTWAIT);
	this->_request_attempts++;
	this->_basic_request.extenedRaw(tmpRaw);
	if (tmpRecvLen <= -1)
	{
		throw RecievingRequestError();
	}
	this->_basic_request = BasicHTTPRequest(std::string(tmpRaw));
}

void HTTPCall::sendResponse(void)
{
	int sendStatus;
	sendStatus = send(this->_client_fd, this->_response.c_str(), this->_response.size(), MSG_DONTWAIT);
	this->_response_attempts++;
	if (sendStatus <= -1)
	{
		throw SendingResponseError();
	}
	this->_bytes_sent += sendStatus;
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

const Server *HTTPCall::getVirtualServer(void) const
{
	return this->_virtual_server;
}

Socket *HTTPCall::getSocket(void) const
{
	return this->_socket;
}

BasicHTTPRequest HTTPCall::getBasicRequest(void) const
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

/* ************************************************************************** */