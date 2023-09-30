
#include <ResponseHeader/ResponseHeader.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ResponseHeader::ResponseHeader(HTTPStatusCode code, const ErrorPageSet &error_page_set)
{
	_defaultConstructor();
	setStatusCode(code);
	if (_isErrorCode(code))
	{
		setContentType(httpConstants::HTML_SUFFIX);
		setConnection(httpConstants::CONNECTION_CLOSE);
		_setErrorPageIfNeeded(code, error_page_set);
		if (code.get() == HTTPStatusCode::METHOD_NOT_ALLOWED)
			_header[CONNECTION].name = httpConstants::ALLOW_HEADER;
	}
}

ResponseHeader::ResponseHeader(const ResponseHeader &src)
	: _header(src.getHeader())
{
}

const char *ResponseHeader::InvalidDefaultPage::what() const throw()
{
	return "Invalid default page";
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ResponseHeader::~ResponseHeader()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ResponseHeader &ResponseHeader::operator=(ResponseHeader const &rhs)
{
	if (this != &rhs)
	{
		this->_header = rhs.getHeader();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, ResponseHeader const &i)
{
	o << converter::vectorToString(i.getResponse());
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void ResponseHeader::_defaultConstructor()
{
	for (field_key f = STANDARD; f <= LOCATION; f = static_cast< field_key >(static_cast< int >(f) + 1))
	{
		Field defaultHeader;
		_header.insert(std::make_pair(f, defaultHeader));
	}
	_header[STANDARD].name = httpConstants::HTTP_VERSION;
	_header[STANDARD].value = "";
	_header[SERVER].name = httpConstants::SERVER_FIELD_KEY;
	_header[SERVER].value = httpConstants::SERVER_FIELD_VALUE;
	_header[DATE].name = httpConstants::DATE_FIELD_KEY;
	_header[DATE].value = _getCurrentDate();
	_header[CONNECTION_TYPE].name = httpConstants::CONTENT_TYPE_FIELD_KEY;
	_header[CONNECTION_TYPE].value = "";
	_header[CONTENT_LENGTH].name = httpConstants::CONTENT_LENGTH_FIELD_KEY;
	_header[CONTENT_LENGTH].value = "";
	_header[CONNECTION].name = httpConstants::CONNECTION_FIELD_KEY;
	_header[LOCATION].value = "";
	_header[LOCATION].name = "";
	setContentType(httpConstants::TXT_SUFFIX);
	_setContentLength(0);
	setConnection(httpConstants::CONNECTION_ALIVE);
}

void ResponseHeader::_setErrorPageIfNeeded(HTTPStatusCode code, const ErrorPageSet &error_page_set)
{
	std::string path(error_page_set.getPage(code.get()));
	if (!path.empty())
	{
		std::ifstream file(path.c_str(), std::ios::binary);
		if (!file)
			throw ResponseHeader::InvalidDefaultPage();

		file.seekg(0, std::ios::end);
		std::streampos fileSize = file.tellg();
		file.seekg(0, std::ios::beg);

		std::vector< char > buffer(fileSize);

		file.read(&buffer[0], fileSize);

		file.close();
		setBody(buffer);
	}
	else
		setBody("<!DOCTYPE html>\n<html>\n<body>\n<h1>" + converter::numToString(code.get()) + httpConstants::SPACE +
				code.toString() + "</h1>\n</body>\n</html>");
}

const std::string ResponseHeader::_getCurrentDate(void)
{
	char buffer[80];
	std::time_t now;
	struct std::tm *time_info;
	std::string result = "";
	now = std::time(0);
	time_info = std::gmtime(&now);
	std::strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", time_info);
	result.reserve(80);
	result = buffer;
	return (result);
}

void ResponseHeader::_setContentLength(size_t length)
{
	this->_header.at(CONTENT_LENGTH).value = converter::numToString(length);
}

bool ResponseHeader::_isErrorCode(HTTPStatusCode code)
{
	return (code.get() >= HTTPStatusCode::BAD_REQUEST);
}

size_t ResponseHeader::_getTotalSize(void) const
{
	size_t totalSize = 0;
	std::map< int, ResponseHeader::Field >::const_iterator it = _header.begin();

	for (; it != _header.end(); it++)
	{
		totalSize += it->second.name.length() + it->second.value.length();
	}
	return (totalSize + _body.size());
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

void ResponseHeader::setStatusCode(HTTPStatusCode code)
{
	std::string value =
		converter::numToString< int >(static_cast< int >(code.get())) + httpConstants::SPACE + code.toString();
	this->_header.at(STANDARD).value = value;
}

void ResponseHeader::setContentType(const std::string &type)
{
	if (ContentTypes::isValid(type) == false)
	{
		this->_header.at(CONNECTION_TYPE).value = ContentTypes(httpConstants::TXT_SUFFIX).get();
		return;
	}
	ContentTypes contentType(type);
	this->_header.at(CONNECTION_TYPE).value = contentType.get();
}

void ResponseHeader::setConnection(const std::string &connection)
{
	this->_header.at(CONNECTION).value = connection;
}

void ResponseHeader::setBody(const std::string &body)
{
	setBody(std::vector< char >(body.begin(), body.end()));
}

void ResponseHeader::setBody(const std::vector< char > &body)
{
	_body = body;

	if (_header[CONTENT_LENGTH].value == "0" || _header[CONTENT_LENGTH].value == "")
		_setContentLength(_body.size());
	if (this->_header.at(CONNECTION_TYPE).value == "")
		setContentType(httpConstants::HTML_SUFFIX);
}

void ResponseHeader::setHeader(const std::string &key, const std::string &value)
{
	static int i = LOCATION + 1;
	for (field_key f = STANDARD; f <= LOCATION; f = static_cast< field_key >(static_cast< int >(f) + 1))
	{
		if (_header.at(f).name.find(key) != std::string::npos)
		{
			_header.at(f).value = value;
			return;
		}
	}
	_header[i].name = key + ": ";
	_header[i].value = value;
	++i;
	if (i == 10000)
		i = LOCATION + 1;
}

void ResponseHeader::setLocationHeader(const std::string &value)
{
	this->_header[LOCATION].value = value;
	this->_header[LOCATION].name = httpConstants::headers::LOCATION + httpConstants::SEPARATOR + httpConstants::SPACE;
}

const std::string ResponseHeader::getStatusMessage()
{
	return (this->_header.at(STANDARD).value);
}

const std::string ResponseHeader::getContentType()
{
	return (this->_header.at(CONNECTION_TYPE).value);
}

const std::vector< char > &ResponseHeader::getBody()
{
	return _body;
}

const std::string ResponseHeader::getConnection()
{
	return (this->_header.at(CONNECTION).value);
}

const std::map< int, ResponseHeader::Field > ResponseHeader::getHeader() const
{
	return (_header);
}

const std::vector< char > ResponseHeader::getResponse() const
{
	std::vector< char > res;
	try
	{
		res.reserve(_getTotalSize());

		std::map< int, ResponseHeader::Field >::const_iterator it = _header.begin();

		for (; it != _header.end(); it++)
		{
			if (it->second.name == "" || it->second.value == "")
				continue;
			std::string tmp = it->second.name + it->second.value + httpConstants::FIELD_BREAK;
			res.insert(res.end(), tmp.begin(), tmp.end());
		}
		std::string tmp = httpConstants::FIELD_BREAK;
		res.insert(res.end(), tmp.begin(), tmp.end());
		res.insert(res.end(), _body.begin(), _body.end());
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		res.empty();
	}
	return res;
}

/* ************************************************************************** */
