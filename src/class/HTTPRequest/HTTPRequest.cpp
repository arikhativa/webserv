#include <HTTPRequest/HTTPRequest.hpp>

const std::string HTTPRequest::GET_STRING("GET ");
const std::string HTTPRequest::POST_STRING("POST ");
const std::string HTTPRequest::DELETE_STRING("DELETE ");

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

const int HTTPRequest::MAX_REQUEST_ATTEMPTS = 10;

HTTPRequest::HTTPRequest(const Server virtualServer, int clientFd)
	: _attempts(0)
	, _virtualServer(virtualServer)
	, _clientFd(clientFd)
	, _response("\0")
	, _basicRequest("")
{
}

const char *HTTPRequest::SendingResponseError::what() const throw()
{
	return "Couldn't send response: send() failed";
}

const char *HTTPRequest::RecievingRequestError::what() const throw()
{
	return "Didn't recieve request: recv() failed";
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

HTTPRequest::~HTTPRequest()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

std::ostream &operator<<(std::ostream &o, HTTPRequest const &i)
{
	o << "HTTPRequest[" << i.getBasicRequest() << "]";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

BasicHTTPRequest::Type HTTPRequest::getRequestType()
{
	return this->_basicRequest.getType();
}

void HTTPRequest::recvRequest(void)
{
	int tmpRecvLen;
	char tmpRaw[4096];

	tmpRecvLen = recv(this->_clientFd, tmpRaw, sizeof(tmpRaw), MSG_DONTWAIT);
	if (tmpRecvLen <= -1)
	{
		this->_attempts++;
		throw RecievingRequestError();
	}
	this->_basicRequest = BasicHTTPRequest(std::string(tmpRaw));
}

void HTTPRequest::sendResponse(void)
{
	int sendStatus;
	sendStatus = send(this->_clientFd, this->_response.c_str(), this->_response.size(), MSG_DONTWAIT);
	if (sendStatus <= -1)
	{
		this->_attempts++;
		throw SendingResponseError();
	}
}

void HTTPRequest::handleRequest(void)
{
	switch (getRequestType())
	{
	case BasicHTTPRequest::GET:
		this->_response = HTTPRequestHandler::get::GET(this->_virtualServer, this->_basicRequest);
		break;
	case BasicHTTPRequest::POST:
		this->_response = HTTPRequestHandler::post::POST(this->_virtualServer, this->_basicRequest);
		break;
	case BasicHTTPRequest::DELETE:
		this->_response = HTTPRequestHandler::delete_::DELETE(this->_virtualServer, this->_basicRequest);
		break;
	default: // Uknown request
		this->_response = HTTPRequestHandler::unknown::UNKNOWN(this->_virtualServer, this->_basicRequest);
		break;
	}
}

void HTTPRequest::terminate(void)
{
	close(this->_clientFd);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

BasicHTTPRequest HTTPRequest::getBasicRequest(void) const
{
	return this->_basicRequest;
}

std::string HTTPRequest::getResponse(void) const
{
	return this->_response;
}

int HTTPRequest::getClientFd(void) const
{
	return this->_clientFd;
}

int HTTPRequest::getAttempts(void) const
{
	return this->_attempts;
}

void HTTPRequest::setBasicRequest(BasicHTTPRequest request)
{
	this->_basicRequest = request;
}

void HTTPRequest::setResponse(std::string response)
{
	this->_response = response;
}

/* ************************************************************************** */