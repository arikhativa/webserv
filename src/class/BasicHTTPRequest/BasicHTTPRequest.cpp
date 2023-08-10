
#include <BasicHTTPRequest/BasicHTTPRequest.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

BasicHTTPRequest::BasicHTTPRequest(const std::string &raw_request)
	: _raw(raw_request)
	, _type(_parseType(raw_request))
	, _path(_parsePath(raw_request))
	, _query(_parseQuery(raw_request))
	, _http_version(_parseHTTPVersion(raw_request))
	, _headers(_parseHeaders(raw_request))
{
}

BasicHTTPRequest::BasicHTTPRequest(const BasicHTTPRequest &src)
	: _raw(src._raw)
	, _type(src._type)
	, _path(src._path)
	, _query(src._query)
	, _http_version(src._http_version)
	, _headers(src._headers)
	, _body(src._body)
{
}

BasicHTTPRequest::InvalidRequestException::InvalidRequestException(const std::string &msg)
	: _msg("Invalid request: " + msg)
{
}

const char *BasicHTTPRequest::InvalidRequestException::what() const throw()
{
	return _msg.c_str();
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

BasicHTTPRequest::~BasicHTTPRequest()
{
}

BasicHTTPRequest::InvalidRequestException::~InvalidRequestException() throw()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

BasicHTTPRequest &BasicHTTPRequest::operator=(BasicHTTPRequest const &rhs)
{
	if (this != &rhs)
	{
		this->_type = rhs._type;
		this->_path = rhs._path;
		this->_query = rhs._query;
		this->_http_version = rhs._http_version;
		this->_headers = rhs._headers;
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, BasicHTTPRequest const &i)
{
	std::string type = "UNKNOWN";
	std::string http_version = "UNKNOWN";

	if (i.getHTTPVersion() == BasicHTTPRequest::HTTP_0_9)
		http_version = "HTTP/0.9";
	else if (i.getHTTPVersion() == BasicHTTPRequest::HTTP_1_0)
		http_version = "HTTP/1.0";
	else if (i.getHTTPVersion() == BasicHTTPRequest::HTTP_1_1)
		http_version = "HTTP/1.1";
	else if (i.getHTTPVersion() == BasicHTTPRequest::HTTP_2_0)
		http_version = "HTTP/2.0";
	else if (i.getHTTPVersion() == BasicHTTPRequest::HTTP_3)
		http_version = "HTTP/3";

	if (i.getType() == BasicHTTPRequest::GET)
		type = "GET";
	else if (i.getType() == BasicHTTPRequest::POST)
		type = "POST";
	else if (i.getType() == BasicHTTPRequest::DELETE)
		type = "DELETE";

	o << "{\"_type\": \"" << type << "\","
	  << "\"_path\": \"" << i.getPath() << "\","
	  << "\"_query\": \"" << i.getQuery() << "\","
	  << "\"_http_version\": \"" << http_version << "\","
	  << "\"_headers\": " << i.getHeaders() << "}";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

BasicHTTPRequest::Type BasicHTTPRequest::_parseType(const std::string &raw_request)
{
	if (raw_request.find("GET") == 0)
		return BasicHTTPRequest::GET;
	else if (raw_request.find("POST") == 0)
		return BasicHTTPRequest::POST;
	else if (raw_request.find("DELETE") == 0)
		return BasicHTTPRequest::DELETE;
	throw BasicHTTPRequest::InvalidRequestException("Bad type.");
}

Path BasicHTTPRequest::_parsePath(const std::string &raw_request)
{
	std::size_t start = raw_request.find("/");
	std::size_t query_pos = raw_request.find("?", start);
	std::size_t end = raw_request.find(" ", start);

	if (start == std::string::npos)
		throw BasicHTTPRequest::InvalidRequestException("Missing path.");
	if (query_pos != std::string::npos && end > query_pos)
		end = query_pos;
	if (end == std::string::npos)
		throw BasicHTTPRequest::InvalidRequestException("Bad path.");

	return Path(raw_request.substr(start, end - start));
}

std::string BasicHTTPRequest::_parseQuery(const std::string &raw_request)
{
	std::size_t start = raw_request.find("/");
	std::size_t query_pos = raw_request.find("?", start);
	std::size_t end = raw_request.find(" ", start);

	if (query_pos == std::string::npos || query_pos > end)
		return "";
	end = raw_request.find(" ", query_pos);
	if (end == std::string::npos)
		throw BasicHTTPRequest::InvalidRequestException("Bad query.");
	return raw_request.substr(query_pos, end - query_pos);
}

BasicHTTPRequest::HTTPVersion BasicHTTPRequest::_parseHTTPVersion(const std::string &raw_request)
{
	std::size_t start = raw_request.find("HTTP/");

	if (start == std::string::npos)
		throw BasicHTTPRequest::InvalidRequestException("Bad http version.");

	std::size_t end = raw_request.find(httpConstants::FIELD_BREAK, start);
	std::string version = raw_request.substr(start, end - start);
	if (version == "HTTP/0.9")
		return BasicHTTPRequest::HTTP_0_9;
	else if (version == "HTTP/1.0")
		return BasicHTTPRequest::HTTP_1_0;
	else if (version == "HTTP/1.1")
		return BasicHTTPRequest::HTTP_1_1;
	else if (version == "HTTP/2.0")
		return BasicHTTPRequest::HTTP_2_0;
	else if (version == "HTTP/3")
		return BasicHTTPRequest::HTTP_3;
	return BasicHTTPRequest::UNKNOWN;
}

std::map<std::string, std::string> BasicHTTPRequest::_parseHeaders(const std::string &raw_request)
{
	std::map<std::string, std::string> headers;

	std::size_t start = raw_request.find(httpConstants::FIELD_BREAK);
	if (start == std::string::npos)
		return headers;

	start += 2;
	std::size_t end = raw_request.find(httpConstants::FIELD_BREAK, start);

	if (start != std::string::npos && end == std::string::npos)
		throw BasicHTTPRequest::InvalidRequestException("Bad header: missing end of header");

	while (end != std::string::npos && start != end)
	{
		std::size_t colon_pos = raw_request.find(":", start);
		if (colon_pos > end)
			throw BasicHTTPRequest::InvalidRequestException("Bad header: missing colon");

		std::string key = raw_request.substr(start, colon_pos - start);

		colon_pos += 2;
		std::string value = raw_request.substr(colon_pos, end - colon_pos);
		headers[key] = value;

		start = end + 2;
		end = raw_request.find(httpConstants::FIELD_BREAK, start);
	}
	return headers;
}

bool BasicHTTPRequest::isChunked(void) const
{
	std::map<std::string, std::string>::const_iterator it = _headers.find(httpConstants::headers::TRANSFER_ENCODING);
	if (it == _headers.end())
		return false;
	return it->second == httpConstants::headers::CHUNKED;
}

void BasicHTTPRequest::setBody(void)
{
	std::map<std::string, std::string>::const_iterator it = _headers.find(httpConstants::headers::CONTENT_LENGTH);
	if (it == _headers.end())
		return;

	std::size_t content_length = converter::stringToSizeT(it->second);

	std::size_t start = _raw.find(httpConstants::HEADER_BREAK);
	if (start == std::string::npos)
		return;
	start += 4;
	_body = _raw.substr(start, content_length);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

const std::string &BasicHTTPRequest::getRawRequest(void) const
{
	return this->_raw;
}

BasicHTTPRequest::Type BasicHTTPRequest::getType(void) const
{
	return this->_type;
}

const std::string &BasicHTTPRequest::getPath(void) const
{
	return this->_path.get();
}

const std::string &BasicHTTPRequest::getQuery(void) const
{
	return this->_query;
}

BasicHTTPRequest::HTTPVersion BasicHTTPRequest::getHTTPVersion(void) const
{
	return this->_http_version;
}

const std::map<std::string, std::string> &BasicHTTPRequest::getHeaders(void) const
{
	return this->_headers;
}

const std::string &BasicHTTPRequest::getBody(void) const
{
	return this->_body;
}

/* ************************************************************************** */
