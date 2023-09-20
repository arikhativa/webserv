
#include <HTTPStatusCode/HTTPStatusCode.hpp>

static std::map< HTTPStatusCode::Code, std::string > initMap(void)
{
	std::map< HTTPStatusCode::Code, std::string > map;

	// 1xx Informational
	map[HTTPStatusCode::CONTINUE] = "Continue";
	map[HTTPStatusCode::SWITCHING_PROTOCOLS] = "Switching Protocols";

	// 2xx Successful
	map[HTTPStatusCode::OK] = "OK";
	map[HTTPStatusCode::CREATED] = "Created";
	map[HTTPStatusCode::ACCEPTED] = "Accepted";
	map[HTTPStatusCode::NON_AUTHORITATIVE_INFORMATION] = "Non-Authoritative Information";
	map[HTTPStatusCode::NO_CONTENT] = "No Content";
	map[HTTPStatusCode::RESET_CONTENT] = "Reset Content";
	map[HTTPStatusCode::PARTIAL_CONTENT] = "Partial Content";

	// 3xx Redirection
	map[HTTPStatusCode::MULTIPLE_CHOICES] = "Multiple Choices";
	map[HTTPStatusCode::MOVED_PERMANENTLY] = "Moved Permanently";
	map[HTTPStatusCode::FOUND] = "Found";
	map[HTTPStatusCode::SEE_OTHER] = "See Other";
	map[HTTPStatusCode::NOT_MODIFIED] = "Not Modified";
	map[HTTPStatusCode::USE_PROXY] = "Use Proxy";
	map[HTTPStatusCode::UNUSED] = "Unused";
	map[HTTPStatusCode::TEMPORARY_REDIRECT] = "Temporary Redirect";

	// 4xx Client Error
	map[HTTPStatusCode::BAD_REQUEST] = "Bad Request";
	map[HTTPStatusCode::UNAUTHORIZED] = "Unauthorized";
	map[HTTPStatusCode::PAYMENT_REQUIRED] = "Payment Required";
	map[HTTPStatusCode::FORBIDDEN] = "Forbidden";
	map[HTTPStatusCode::NOT_FOUND] = "Not Found";
	map[HTTPStatusCode::METHOD_NOT_ALLOWED] = "Method Not Allowed";
	map[HTTPStatusCode::NOT_ACCEPTABLE] = "Not Acceptable";
	map[HTTPStatusCode::PROXY_AUTHENTICATION_REQUIRED] = "Proxy Authentication Required";
	map[HTTPStatusCode::REQUEST_TIMEOUT] = "Request Timeout";
	map[HTTPStatusCode::CONFLICT] = "Conflict";
	map[HTTPStatusCode::GONE] = "Gone";
	map[HTTPStatusCode::LENGTH_REQUIRED] = "Length Required";
	map[HTTPStatusCode::PRECONDITION_FAILED] = "Precondition Failed";
	map[HTTPStatusCode::REQUEST_ENTITY_TOO_LARGE] = "Request Entity Too Large";
	map[HTTPStatusCode::REQUEST_URI_TOO_LONG] = "Request-URI Too Long";
	map[HTTPStatusCode::UNSUPPORTED_MEDIA_TYPE] = "Unsupported Media Type";
	map[HTTPStatusCode::REQUESTED_RANGE_NOT_SATISFIABLE] = "Requested Range Not Satisfiable";
	map[HTTPStatusCode::EXPECTATION_FAILED] = "Expectation Failed";

	// 5xx Server Error
	map[HTTPStatusCode::INTERNAL_SERVER_ERROR] = "Internal Server Error";
	map[HTTPStatusCode::NOT_IMPLEMENTED] = "Not Implemented";
	map[HTTPStatusCode::BAD_GATEWAY] = "Bad Gateway";
	map[HTTPStatusCode::SERVICE_UNAVAILABLE] = "Service Unavailable";
	map[HTTPStatusCode::GATEWAY_TIMEOUT] = "Gateway Timeout";
	map[HTTPStatusCode::HTTP_VERSION_NOT_SUPPORTED] = "HTTP Version Not Supported";

	return map;
}

const std::map< HTTPStatusCode::Code, std::string > HTTPStatusCode::_map(initMap());

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

HTTPStatusCode::HTTPStatusCode(const std::string &code)
{
	int int_code = std::atoi(code.c_str());

	if (!HTTPStatusCode::isValid(int_code))
		throw HTTPStatusCode::InvalidStatusCodeException();
	this->_code = static_cast< HTTPStatusCode::Code >(int_code);
}

HTTPStatusCode::HTTPStatusCode(int code)
{
	if (!HTTPStatusCode::isValid(code))
		throw HTTPStatusCode::InvalidStatusCodeException();
	this->_code = static_cast< HTTPStatusCode::Code >(code);
}

HTTPStatusCode::HTTPStatusCode(HTTPStatusCode::Code code)
	: _code(code)
{
}

HTTPStatusCode::HTTPStatusCode(const HTTPStatusCode &src)
	: _code(src.get())
{
}

const char *HTTPStatusCode::InvalidStatusCodeException::what() const throw()
{
	return "Invalid status code";
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

HTTPStatusCode::~HTTPStatusCode()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

HTTPStatusCode &HTTPStatusCode::operator=(HTTPStatusCode const &rhs)
{
	if (this != &rhs)
	{
		this->_code = rhs.get();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, HTTPStatusCode const &i)
{
	o << i.get() << " " << i.toString();
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

bool HTTPStatusCode::isValid(int code)
{
	return (code >= 100 && code <= 101) || (code >= 200 && code <= 206) || (code >= 300 && code <= 307) ||
		   (code >= 400 && code <= 417) || (code >= 500 && code <= 505);
}

std::string HTTPStatusCode::toString(void) const
{
	return HTTPStatusCode::_map.at(this->_code);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

void HTTPStatusCode::set(HTTPStatusCode::Code code)
{
	this->_code = code;
}

void HTTPStatusCode::set(const std::string &code)
{
	int int_code = std::atoi(code.c_str());

	if (!HTTPStatusCode::isValid(int_code))
		throw HTTPStatusCode::InvalidStatusCodeException();
	this->_code = static_cast< HTTPStatusCode::Code >(int_code);
}

void HTTPStatusCode::set(int code)
{
	if (!HTTPStatusCode::isValid(code))
		throw HTTPStatusCode::InvalidStatusCodeException();
	this->_code = static_cast< HTTPStatusCode::Code >(code);
}

HTTPStatusCode::Code HTTPStatusCode::get(void) const
{
	return this->_code;
}

/* ************************************************************************** */
