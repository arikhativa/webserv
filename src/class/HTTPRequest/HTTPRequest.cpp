#include <HTTPRequest/HTTPRequest.hpp>

const std::string HTTPRequest::GET_STRING("GET ");
const std::string HTTPRequest::POST_STRING("POST ");
const std::string HTTPRequest::DELETE_STRING("DELETE ");

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

const int HTTPRequest::MAX_REQUEST_ATTEMPTS = 10;

HTTPRequest::HTTPRequest(const Server virtualServer, int clientFd)
	: _attempts(0), _virtualServer(virtualServer), _clientFd(clientFd), _response("\0")
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

HTTPRequest::type HTTPRequest::getRequestType()
{
	if (!this->_rawRequest.compare(0, HTTPRequest::GET_STRING.size(), GET_STRING))
		return (GET);
	if (!this->_rawRequest.compare(0, HTTPRequest::POST_STRING.size(), POST_STRING))
		return (POST);
	if (!this->_rawRequest.compare(0, HTTPRequest::DELETE_STRING.size(), DELETE_STRING))
		return (DELETE);
	else
		return (UNKNOWN);
}

#include <vector>

void HTTPRequest::recvRequest(void)
{
    int tmpRecvLen;
    unsigned long long int maxRequestSize = 99999;
    std::vector<char> tmpRaw;

    while (true)
    {
        std::vector<char> buffer(maxRequestSize);
        tmpRecvLen = recv(this->_clientFd, buffer.data(), maxRequestSize, MSG_DONTWAIT);

        if (tmpRecvLen <= 0)
        {
            if (tmpRaw.empty())
            {
                this->_attempts++;
                throw RecievingRequestError();
            }
            else
            {
                break; // Se ha recibido toda la solicitud
            }
        }

        // Agregar los datos recibidos al vector tmpRaw
        tmpRaw.insert(tmpRaw.end(), buffer.begin(), buffer.begin() + tmpRecvLen);
    }

    this->_rawRequest = std::string(tmpRaw.begin(), tmpRaw.end());
}


void HTTPRequest::sendResponse(void)
{
	int sendStatus;
	sendStatus = send(this->_clientFd, this->_response.c_str(), this->_response.size(), 0);
	if (sendStatus <= -1)
	{
		this->_attempts++;
		throw SendingResponseError();
	}
}

/* TODO: handle request according to HTTP */
void HTTPRequest::handleRequest(void)
{
	switch (getRequestType())
	{
		case HTTPRequest::GET:
			this->_response = HTTPRequestHandler::get::GET(this->_virtualServer, this->_rawRequest);
			break;
		case HTTPRequest::POST:
			this->_response = HTTPRequestHandler::post::POST(this->_virtualServer, this->_rawRequest);
			break;
		case HTTPRequest::DELETE:
			this->_response = HTTPRequestHandler::delete_::DELETE(this->_virtualServer, this->_rawRequest);
			break;
		default: //Uknown request
			this->_response = HTTPRequestHandler::unknown::UNKNOWN(this->_virtualServer, this->_rawRequest);
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

int HTTPRequest::getAttempts(void) const
{
	return this->_attempts;
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