
#include <BasicHTTPRequest/BasicHTTPRequest.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

BasicHTTPRequest::BasicHTTPRequest(const std::string &raw_request)
	: ABaseHTTPCall(raw_request)
	, _type(BasicHTTPRequest::GET)
	, _path("")
	, _query("")
{
}

BasicHTTPRequest::BasicHTTPRequest(const BasicHTTPRequest &src)
	: ABaseHTTPCall(src)
	, _type(src.getType())
	, _path(src.getPath())
	, _query(src.getQuery())
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

BasicHTTPRequest::~BasicHTTPRequest()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

BasicHTTPRequest &BasicHTTPRequest::operator=(BasicHTTPRequest const &rhs)
{
	if (this != &rhs)
	{
		ABaseHTTPCall::operator=(rhs);
		this->_type = rhs.getType();
		this->_path = rhs._path;
		this->_query = rhs.getQuery();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, BasicHTTPRequest const &i)
{
	std::string type(BasicHTTPRequest::toStringType(i.getType()));
	std::string http_version(ABaseHTTPCall::toStringVersion(i.getHTTPVersion()));

	o << "{\"_type\": \"" << type << "\","
	  << "\"_path\": \"" << i.getPath() << "\","
	  << "\"_query\": \"" << i.getQuery() << "\","
	  << "\"_http_version\": \"" << http_version << "\","
	  << "\"_headers\": " << i.getHeaders() << ","
	  << "\"_body\": \"" << i.getBodyAsString() << "\""
	  << "}";

	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void BasicHTTPRequest::setPath(const std::string &path)
{
	this->_path.set(path);
}

static std::map< BasicHTTPRequest::Type, std::string > initTypeMap(void)
{
	std::map< BasicHTTPRequest::Type, std::string > ret;

	ret[BasicHTTPRequest::GET] = "GET";
	ret[BasicHTTPRequest::POST] = "POST";
	ret[BasicHTTPRequest::DELETE] = "DELETE";

	return ret;
}

std::string BasicHTTPRequest::toSimplifiedHTTP(void) const
{
	std::string type(BasicHTTPRequest::toStringType(getType()));
	std::string http_version(ABaseHTTPCall::toStringVersion(getHTTPVersion()));

	std::string ret;

	ret += type + httpConstants::SPACE + this->getPath();

	converter::mergeSpaces(ret);
	return ret;
}

std::string BasicHTTPRequest::toStringType(BasicHTTPRequest::Type t)
{
	static const std::map< BasicHTTPRequest::Type, std::string > m(initTypeMap());

	return m.at(t);
}

void BasicHTTPRequest::parseRaw(void)
{
	_type = _parseType(this->getRawRequest());
	_path = _parsePath(this->getRawRequest());
	_query = _parseQuery(this->getRawRequest());
	ABaseHTTPCall::_parseHTTPVersion();
	ABaseHTTPCall::_parseHeaders();
}

std::string BasicHTTPRequest::toString(void) const
{
	std::string type(BasicHTTPRequest::toStringType(getType()));
	std::string http_version(ABaseHTTPCall::toStringVersion(getHTTPVersion()));

	std::string ret;

	ret += type + httpConstants::SPACE + this->getPath();

	if (!this->getQuery().empty())
		ret += httpConstants::SPACE + this->getQuery();
	ret += httpConstants::SPACE + http_version + httpConstants::FIELD_BREAK +
		   converter::headersToString(this->getHeaders()) + getBodyAsString();

	return ret;
}

BasicHTTPRequest::Type BasicHTTPRequest::_parseType(const std::string &raw_request)
{
	if (raw_request.find("GET") == 0)
		return BasicHTTPRequest::GET;
	else if (raw_request.find("POST") == 0)
		return BasicHTTPRequest::POST;
	else if (raw_request.find("DELETE") == 0)
		return BasicHTTPRequest::DELETE;

	// DELETE because it is the longest type
	if (raw_request.size() >= std::strlen("DELETE"))
		throw Invalid("Bad type: " + raw_request);
	throw Incomplete("Missing type");
}

Path BasicHTTPRequest::_parsePath(const std::string &raw_request)
{
	std::size_t start = raw_request.find("/");
	std::size_t query_pos = raw_request.find("?", start);
	std::size_t end = raw_request.find(" ", start);
	std::size_t end_of_line = raw_request.find(httpConstants::FIELD_BREAK);

	if (end_of_line != std::string::npos)
	{
		if (start == std::string::npos)
			throw Invalid("Missing path");
		if (query_pos != std::string::npos && end > query_pos)
			end = query_pos;
		if (end == std::string::npos)
			throw Invalid("Missing end of path");
	}
	else
	{
		if (start == std::string::npos)
			throw Incomplete("Missing path");
		if (query_pos != std::string::npos && end > query_pos)
			end = query_pos;
		if (end == std::string::npos)
			throw Incomplete("Missing end of path");
	}
	return Path(converter::urlDecode(raw_request.substr(start, end - start)));
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
		throw Invalid("Bad query.");
	return raw_request.substr(query_pos, end - query_pos);
}

void BasicHTTPRequest::unParse(void)
{
	ABaseHTTPCall::unParse();
	_type = BasicHTTPRequest::GET;
	_path = Path();
	_query = "";
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

bool BasicHTTPRequest::isMultiForm(void) const
{
	std::map< std::string, std::string >::const_iterator it(
		this->getHeaders().find(httpConstants::headers::CONTENT_TYPE));

	if (it != this->getHeaders().end())
	{
		return it->second.find(httpConstants::headers::FROM_DATA) != std::string::npos;
	}
	return false;
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

std::string BasicHTTPRequest::getHost(void) const
{
	try
	{
		return getHeaders().at(httpConstants::headers::HOST);
	}
	catch (const std::exception &e)
	{
		return std::string("");
	}
}
/* ************************************************************************** */
