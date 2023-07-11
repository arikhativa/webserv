
#include <HTTPRequest/HTTPRequest.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

HTTPRequest::HTTPRequest(int clientFd)
	: _clientFd(clientFd)
{
}

HTTPRequest::HTTPRequest(const HTTPRequest &src)
	: _clientFd(src.getClientFd()), _rawRequest(src.getRawRequest()), _response(src.getResponse())
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

HTTPRequest::~HTTPRequest()
{
	close(this->_clientFd);
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

HTTPRequest &HTTPRequest::operator=(HTTPRequest const &rhs)
{
	if (this != &rhs)
	{
		this->_clientFd = rhs.getClientFd();
		this->_rawRequest = rhs.getRawRequest();
		this->_response = rhs.getResponse();
	}
	return *this;
}

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
	this->_rawRequest = std::string(tmpRaw, tmpRecvLen);
}

void HTTPRequest::sendResponse(void)
{
	send(this->_clientFd, this->_response.c_str(), this->_response.size(), 0);
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

void HTTPRequest::setClientFd(int fd)
{
	this->_clientFd = fd;
}

/* ************************************************************************** */
