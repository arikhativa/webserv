
#include <HTTPRequest/HTTPRequest.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

HTTPRequest::HTTPRequest(std::string rawRequest)
	: _rawRequest(rawRequest)
{
}

HTTPRequest::HTTPRequest(const HTTPRequest &src)
	: _rawRequest(src.getRawRequest())
{
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

HTTPRequest &HTTPRequest::operator=(HTTPRequest const &rhs)
{
	if (this != &rhs)
	{
		this->_rawRequest = rhs.getRawRequest();
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

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string HTTPRequest::getRawRequest(void) const
{
	return this->_rawRequest;
}

/* ************************************************************************** */
