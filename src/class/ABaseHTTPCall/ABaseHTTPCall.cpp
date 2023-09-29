
#include <ABaseHTTPCall/ABaseHTTPCall.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ABaseHTTPCall::ABaseHTTPCall(const std::string &raw_request)
	: _raw(raw_request)
	, _http_version(UNKNOWN)
{
}

ABaseHTTPCall::ABaseHTTPCall(const ABaseHTTPCall &src)
	: _raw(src.getRawRequest())
	, _headers(src.getHeaders())
	, _http_version(src.getHTTPVersion())
	, _body(src.getBody())
{
}

ABaseHTTPCall::Incomplete::Incomplete(const std::string &msg)
	: _msg("Incomplete call: " + msg)
{
	converter::mergeSpaces(_msg);
}

const char *ABaseHTTPCall::Incomplete::what() const throw()
{
	return _msg.c_str();
}

ABaseHTTPCall::Invalid::Invalid(const std::string &msg)
	: _msg("Invalid call: " + msg)
{
	converter::mergeSpaces(_msg);
}

const char *ABaseHTTPCall::Invalid::what() const throw()
{
	return _msg.c_str();
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ABaseHTTPCall::~ABaseHTTPCall()
{
}

ABaseHTTPCall::Incomplete::~Incomplete() throw()
{
}

ABaseHTTPCall::Invalid::~Invalid() throw()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ABaseHTTPCall &ABaseHTTPCall::operator=(ABaseHTTPCall const &rhs)
{
	if (this != &rhs)
	{
		this->_raw = rhs.getRawRequest();
		this->_headers = rhs.getHeaders();
		this->_http_version = rhs.getHTTPVersion();
		this->_body = rhs.getBody();
	}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

bool ABaseHTTPCall::isBody(void) const
{
	std::map< std::string, std::string >::const_iterator content_length =
		_headers.find(httpConstants::headers::CONTENT_LENGTH);
	std::map< std::string, std::string >::const_iterator transfer_encoding =
		_headers.find(httpConstants::headers::TRANSFER_ENCODING);

	if (content_length != _headers.end() && content_length->second != "0")
		return true;

	if (transfer_encoding != _headers.end())
		return true;

	return false;
}

static std::map< ABaseHTTPCall::HTTPVersion, std::string > initVersionMap(void)
{
	std::map< ABaseHTTPCall::HTTPVersion, std::string > ret;

	ret[ABaseHTTPCall::UNKNOWN] = "UNKNOWN";
	ret[ABaseHTTPCall::HTTP_0_9] = "HTTP/0.9";
	ret[ABaseHTTPCall::HTTP_1_0] = "HTTP/1.0";
	ret[ABaseHTTPCall::HTTP_1_1] = "HTTP/1.1";
	ret[ABaseHTTPCall::HTTP_2_0] = "HTTP/2.0";
	ret[ABaseHTTPCall::HTTP_3_0] = "HTTP/3.0";

	return ret;
}

std::string ABaseHTTPCall::toStringVersion(ABaseHTTPCall::HTTPVersion v)
{
	static const std::map< HTTPVersion, std::string > m(initVersionMap());

	return m.at(v);
}

static size_t findEndOfHTTPVersion(const std::string &s, size_t i)
{
	while (s[i])
	{
		if (s[i] == '\r' || s[i] == ' ')
			return i;
		++i;
	}
	return std::string::npos;
}

void ABaseHTTPCall::_parseHTTPVersion(void)
{
	std::size_t start = _raw.find(httpConstants::HTTP_VERSION_PREFIX);
	std::size_t filed_break = _raw.find(httpConstants::FIELD_BREAK);

	if (start == std::string::npos)
		throw ABaseHTTPCall::Incomplete("HTTP version not found");
	if (filed_break == std::string::npos)
		throw ABaseHTTPCall::Incomplete("missing filed break");

	std::size_t end = findEndOfHTTPVersion(_raw, start);
	if (end == std::string::npos)
		throw ABaseHTTPCall::Incomplete("HTTP version has invalid end");

	std::string version = _raw.substr(start, end - start);

	if (version == toStringVersion(HTTP_0_9))
		_http_version = HTTP_0_9;
	else if (version == toStringVersion(HTTP_1_0))
		_http_version = HTTP_1_0;
	else if (version == toStringVersion(HTTP_1_1))
		_http_version = HTTP_1_1;
	else if (version == toStringVersion(HTTP_2_0))
		_http_version = HTTP_2_0;
	else if (version == toStringVersion(HTTP_3_0))
		_http_version = HTTP_3_0;
	else
		_http_version = UNKNOWN;

	if (_http_version != HTTP_1_1)
		throw ABaseHTTPCall::Invalid("unsupported HTTP version: " + version);
}

bool ABaseHTTPCall::isKeyRestricted(const std::string &key)
{
	return (key == httpConstants::headers::HOST || key == httpConstants::headers::DATE ||
			key == httpConstants::headers::CONTENT_LENGTH);
}

void ABaseHTTPCall::_parseHeaders(void)
{
	std::size_t start = _raw.find(httpConstants::FIELD_BREAK);
	if (start == std::string::npos)
		throw ABaseHTTPCall::Incomplete("Bad header: missing start of header");

	start += 2;
	std::size_t end = _raw.find(httpConstants::FIELD_BREAK, start);

	if (end == std::string::npos)
		throw ABaseHTTPCall::Incomplete("Bad header: missing end of the first header");

	while (end != std::string::npos && start != end)
	{
		std::size_t colon_pos = _raw.find(":", start);
		if (colon_pos > end)
			throw ABaseHTTPCall::Invalid("Bad header: missing colon");

		std::string key = converter::toNginxStyle(_raw.substr(start, colon_pos - start));

		colon_pos += 2;
		std::string value = _raw.substr(colon_pos, end - colon_pos);
		if (isKeyRestricted(key) && !_headers[key].empty())
		{
			throw ABaseHTTPCall::Invalid("Bad header: duplicate restricted key: " + key);
		}
		if (_headers[key].empty())
			_headers[key] = value;
		else
			_headers[key] += ", " + value;

		start = end + 2;
		end = _raw.find(httpConstants::FIELD_BREAK, start);
	}
}

void ABaseHTTPCall::parseBody(void)
{
	if (isChunked())
		_parseBodyByChunked();
	else
		_parseBodyByContentLength();
}

void printVector(const std::vector< char > &vec, int content_length)
{
	std::vector< char >::const_iterator it = vec.begin();
	int i = 0;
	while (i < content_length && it != vec.end())
	{
		std::cout << *it;
		++it;
		++i;
	}
	std::cout << std::endl;
}

size_t findInVector(const std::vector< char > &buff, const std::vector< char > &find)
{
	for (size_t i = 0; i <= buff.size() - find.size(); ++i)
	{
		bool found = true;
		for (size_t j = 0; j < find.size(); ++j)
		{
			if (buff[i + j] != find[j])
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			return i;
		}
	}
	return std::string::npos; // Not found
}

// TODO check with bad content length
void ABaseHTTPCall::_parseBodyByContentLength(void)
{
	std::map< std::string, std::string >::const_iterator it = _headers.find(httpConstants::headers::CONTENT_LENGTH);
	if (it == _headers.end())
		throw ABaseHTTPCall::Invalid("missing content length");

	std::size_t content_length = converter::stringToSizeT(it->second);

	std::size_t start = _raw.find(httpConstants::HEADER_BREAK);
	if (start == std::string::npos)
		throw ABaseHTTPCall::Incomplete("missing body");

	start += 4;

	// std::vector< char > endOfHeaderVector(httpConstants::HEADER_BREAK.begin(), httpConstants::HEADER_BREAK.end());

	// ::size_t index = findInVector(_bin, endOfHeaderVector);

	// if (index == std::string::npos)
	// 	throw ABaseHTTPCall::Incomplete("missing body");
	// index += 4;

	std::vector< char > tmp;
	tmp = _bin;
	tmp.erase(tmp.begin(), tmp.begin() + start);
	// std::cout << "size: " << tmp.size() << std::endl;
	// std::cout << "content_length: " << content_length << std::endl;

	if (tmp.size() < content_length)
		throw ABaseHTTPCall::Incomplete("body is too short");
	if (tmp.size() > content_length)
	{
		std::cout << "erase: " << content_length << std::endl;
		tmp.erase(tmp.begin() + content_length, tmp.end());
	}
	// std::cout << "tmp: " << std::endl;
	// printVector(tmp, content_length);
	_body = tmp;
}

// TODO chunk does not support binary
void ABaseHTTPCall::_parseBodyByChunked(void)
{
	std::size_t start = _raw.find(httpConstants::HEADER_BREAK);
	if (start == std::string::npos)
		throw ABaseHTTPCall::Incomplete("missing body");
	start += 4;

	std::string tmp = _raw.substr(start, _raw.size() - start);

	if (tmp.find(httpConstants::CHUNKED_END) == std::string::npos)
		throw ABaseHTTPCall::Incomplete("body is too short");

	_body.assign(tmp.begin(), tmp.end());
}

// Note that we don't clear _raw.
void ABaseHTTPCall::unParse(void)
{
	_headers.clear();
	_http_version = UNKNOWN;
	_body.clear();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

bool ABaseHTTPCall::isChunked(void) const
{
	std::map< std::string, std::string >::const_iterator it = _headers.find(httpConstants::headers::TRANSFER_ENCODING);
	if (it == _headers.end())
		return false;
	return it->second == httpConstants::headers::CHUNKED;
}

void ABaseHTTPCall::extenedRaw(const std::string &raw)
{
	this->_raw += raw;
}

void ABaseHTTPCall::extenedRaw(char *buff, int len)
{
	_bin.insert(_bin.end(), buff, buff + len);
}

const std::string &ABaseHTTPCall::getRawRequest(void) const
{
	return this->_raw;
}

ABaseHTTPCall::HTTPVersion ABaseHTTPCall::getHTTPVersion(void) const
{
	return this->_http_version;
}

const std::map< std::string, std::string > &ABaseHTTPCall::getHeaders(void) const
{
	return this->_headers;
}

const std::vector< char > &ABaseHTTPCall::getBody(void) const
{
	return this->_body;
}

std::string ABaseHTTPCall::getBodyAsString(void) const
{
	return std::string(_body.data(), _body.size());
}

// std::string ABaseHTTPCall::getRawBody(void) const
// {
// 	std::size_t start = _raw.find(httpConstants::HEADER_BREAK);
// 	if (start == std::string::npos)
// 		throw ABaseHTTPCall::Invalid("missing body");
// 	start += 4;

// 	return _raw.substr(start, _raw.size() - start);
// }

/* ************************************************************************** */
