
#include <HTTPResponse/HTTPResponse.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

HTTPResponse::HTTPResponse(const std::string &raw)
	: ABaseHTTPCall(raw)
	, _stt(500)
{
}

HTTPResponse::HTTPResponse(const HTTPResponse &src)
	: ABaseHTTPCall(src.getRawRequest())
	, _stt(src.getStatusCode())
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

HTTPResponse::~HTTPResponse()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

HTTPResponse &HTTPResponse::operator=(HTTPResponse const &rhs)
{
	if (this != &rhs)
	{
		ABaseHTTPCall::operator=(rhs);
		this->_stt = rhs.getStatusCode();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, HTTPResponse const &i)
{
	std::string http_version(ABaseHTTPCall::toStringVersion(i.getHTTPVersion()));

	o << "{\"_http_version\": \"" << http_version << "\", "
	  << "\"_stt\": \"" << i.getStatusCode() << "\", "
	  << "\"_headers\": " << i.getHeaders() << ", "
	  << "\"_body\": \"" << i.getBody() << "\""
	  << "}";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void HTTPResponse::unParse(void)
{
	ABaseHTTPCall::unParse();
	_stt.set(500);
}

void HTTPResponse::parseRaw(void)
{
	_parseHTTPVersion();
	_parseStatusLine();
	ABaseHTTPCall::_parseHeaders();
}

std::string HTTPResponse::toString(void) const

{
	std::string ret(ABaseHTTPCall::toStringVersion(getHTTPVersion()));

	ret += httpConstants::SPACE + converter::numToString<int>(_stt.get()) + httpConstants::SPACE + _stt.toString() +
		   httpConstants::FIELD_BREAK;

	ret += converter::headersToString(this->getHeaders()) + this->getBody();
	return ret;
}

// TODO change except?
void HTTPResponse::_parseStatusLine(void)
{
	std::size_t start = _raw.find(httpConstants::SPACE);
	std::size_t end = _raw.find(httpConstants::SPACE, start + 1);
	std::size_t end_of_line = _raw.find(httpConstants::FIELD_BREAK);

	if (end_of_line == std::string::npos)
		throw ABaseHTTPCall::Incomplete("missing end of status line");
	if (start == std::string::npos || end == std::string::npos)
		throw ABaseHTTPCall::Invalid("Invalid status line: " + _raw.substr(0, end_of_line));
	_stt.set(_raw.substr(start, end));
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

HTTPStatusCode HTTPResponse::getStatusCode(void) const
{
	return this->_stt;
}

/* ************************************************************************** */
