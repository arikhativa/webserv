#include <HTTPRequest/HTTPRequest.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

const int HTTPRequest::MAX_CHUNK_ATTEMPTS = 5;

HTTPRequest::HTTPRequest(Server *virtualServer, int clientFd)
	: _virtualServer(virtualServer)
	, _clientFd(clientFd)
	, _requestAttempts(0)
	, _responseAttempts(0)
	, _bytesSent(0)
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

void HTTPRequest::recvRequest(void)
{
	int tmpRecvLen;
	char tmpRaw[4096];

	tmpRecvLen = recv(this->_clientFd, tmpRaw, sizeof(tmpRaw), MSG_DONTWAIT);
	this->_requestAttempts++;
	this->_rawRequest += tmpRaw;
	if (tmpRecvLen <= -1)
	{
		throw RecievingRequestError();
	}
	this->_basicRequest = BasicHTTPRequest(std::string(tmpRaw));
}

void HTTPRequest::sendResponse(void)
{
	int sendStatus;
	sendStatus = send(this->_clientFd, this->_response.c_str(), this->_response.size(), MSG_DONTWAIT);
	this->_responseAttempts++;
	if (sendStatus <= -1)
	{
		throw SendingResponseError();
	}
	this->_bytesSent += sendStatus;
}

void HTTPRequest::handleRequest(void)
{
	switch (this->_basicRequest.getType())
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

void HTTPRequest::terminate(void)
{
	close(this->_clientFd);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

int HTTPRequest::getRequestAttempts(void) const
{
	return this->_requestAttempts;
}

int HTTPRequest::getResponseAttempts(void) const
{
	return this->_responseAttempts;
}

long unsigned int HTTPRequest::getBytesSent(void) const
{
	return this->_bytesSent;
}

Server *HTTPRequest::getVirtualServer(void) const
{
	return this->_virtualServer;
}

Socket *HTTPRequest::getSocket(void) const
{
	return this->_socket;
}

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

Path HTTPRequest::getPathServerDirectory(void) const
{
	Path serverPath(this->_virtualServer->getConf()->getRoot()->get());
	return (serverPath);
}

std::list<const IErrorPage *> HTTPRequest::getErrorPages(void) const
{
	return this->_virtualServer->getErrorPages();
}

std::list<const ILocation *>::const_iterator HTTPRequest::searchMatchLocation(void) const
{
	std::list<const ILocation *>::const_iterator tmp = this->_virtualServer->getConf()->getLocations().end();
	std::list<const ILocation *> locations = this->_virtualServer->getConf()->getLocations();
	for (std::list<const ILocation *>::const_iterator it = locations.begin(); it != locations.end(); it++)
	{
		if ((this->_basicRequest.getPath().find((*it)->getPath().get()) == 0) ||
			(this->_basicRequest.getPath() == "" && (*it)->getPath().get() == "/"))
		{
			if (it == locations.begin())
				tmp = it;
			else if ((*it)->getPath().get().length() > (*tmp)->getPath().get().length())
				tmp = it;
		}
	}
	return (tmp);
}

bool HTTPRequest::isAutoIndexOn(void) const
{
	std::list<const ILocation *>::const_iterator tmp = searchMatchLocation();
	if (tmp != this->_virtualServer->getConf()->getLocations().end())
		return (*tmp)->isAutoIndexOn();
	return (false);
}

bool HTTPRequest::canUpload(void) const
{
	std::list<const ILocation *>::const_iterator tmp = searchMatchLocation();
	if (tmp != this->_virtualServer->getConf()->getLocations().end())
		return (*tmp)->canUpload();
	return (false);
}

bool HTTPRequest::isCgi(void) const
{
	/*std::list<const ILocation *>::const_iterator tmp = searchMatchLocation();
	if (tmp != this->_virtualServer->getConf()->getLocations().end())
		return (*tmp)->isCgi();*/
	return (false);
}

void HTTPRequest::setBasicRequest(BasicHTTPRequest request)
{
	this->_basicRequest = request;
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