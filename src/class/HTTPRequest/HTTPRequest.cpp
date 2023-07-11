
#include <HTTPRequest/HTTPRequest.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

HTTPRequest::HTTPRequest(int clientFd)
	: _clientFd(clientFd)
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
	o << "HTTPRequest[" << i.getRawRequest() << "]";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void HTTPRequest::recvRequest(void)
{
				int MAX_BODY_SIZE = 512;
	int tmpRecvLen;
	char tmpRaw[MAX_BODY_SIZE];

	tmpRecvLen = recv(this->_clientFd, tmpRaw, MAX_BODY_SIZE, 0);
	if (tmpRecvLen <= -1)
		throw RecievingRequestError();
	this->_rawRequest = std::string(tmpRaw, tmpRecvLen);
}

void HTTPRequest::sendResponse(void)
{
	int sendStatus;
	sendStatus = send(this->_clientFd, this->_response.c_str(), this->_response.size(), 0);
	if (sendStatus <= -1)
		throw SendingResponseError();
}

/* TODO: handle request according to HTTP */
void HTTPRequest::handleRequest(void)
{
	this->_response = this->_rawRequest;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string HTTPRequest::getRawRequest(void) const
{
	return this->_rawRequest;
}

std::string HTTPRequest::getResponse(void) const
{
	return this->_response;
}

int HTTPRequest::getClientFd(void) const
{
	return this->_clientFd;
}

void HTTPRequest::setRawRequest(std::string request)
{
	this->_rawRequest = request;
}

void HTTPRequest::setResponse(std::string response)
{
	this->_response = response;
}

/* ************************************************************************** */