
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
	o << i.getResponse();
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void ResponseHeader::_defaultConstructor()
{
	for (field_key f = STANDARD; f <= BODY; f = static_cast<field_key>(static_cast<int>(f) + 1))
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
	_header[CONTENT_LENGTH].name = httpConstants::CONTENT_LENGHT_FIELD_KEY;
	_header[CONTENT_LENGTH].value = "";
	_header[CONNECTION].name = httpConstants::CONNECTION_FIELD_KEY;
	_header[LOCATION].value = "";
	_header[LOCATION].name = "";
	_header[BODY].name = httpConstants::FIELD_BREAK;
	_header[BODY].value = "";
	setContentType(httpConstants::TXT_SUFFIX);
	_setContentLength(0);
	setConnection(httpConstants::CONNECTION_ALIVE);
}

void ResponseHeader::_setErrorPageIfNeeded(HTTPStatusCode code, const ErrorPageSet &error_page_set)
{
	std::string path(error_page_set.getPage(code.get()));
	if (!path.empty())
	{
		std::ifstream file(path.c_str());
		if (!file)
			throw ResponseHeader::InvalidDefaultPage();
		std::stringstream contentStream;
		contentStream << file.rdbuf();
		file.close();
		std::string content = contentStream.str();
		setBody(content);
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
	for (field_key f = STANDARD; f <= BODY; f = static_cast<field_key>(static_cast<int>(f) + 1))
		totalSize += _header.at(f).name.length() + _header.at(f).value.length() + 10;
	return (totalSize);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

void ResponseHeader::setStatusCode(HTTPStatusCode code)
{
	std::string value = converter::numToString(code.get()) + httpConstants::SPACE + code.toString();
	this->_header.at(STANDARD).value = value;
}

void ResponseHeader::setContentType(const std::string &type)
{
	if (ContentTypes::isValid(type) == false)
		throw ContentTypes::InvalidExtensionException();
	ContentTypes contentType(type);
	this->_header.at(CONNECTION_TYPE).value = contentType.get();
}

void ResponseHeader::setConnection(const std::string &connection)
{
	this->_header.at(CONNECTION).value = connection;
}

void ResponseHeader::setBody(const std::string &body)
{

	this->_header[BODY].value = body;
	int length = body.length();
	if (length == 0)
		_setContentLength(length);
	else
		_setContentLength(length + 1);
	if (this->_header.at(CONNECTION_TYPE).value == "")
		setContentType(httpConstants::HTML_SUFFIX);
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

const std::string ResponseHeader::getBody()
{
	return (this->_header.at(BODY).value);
}

const std::string ResponseHeader::getConnection()
{
	return (this->_header.at(CONNECTION).value);
}

const std::map<ResponseHeader::field_key, ResponseHeader::Field> ResponseHeader::getHeader() const
{
	return (_header);
}

const std::string ResponseHeader::getResponse() const
{
	std::string res = "";
	try
	{
		res.reserve(_getTotalSize());
		for (field_key f = STANDARD; f <= BODY; f = static_cast<field_key>(static_cast<int>(f) + 1))
		{
			std::string key = "";
			if (_header.find(f) != _header.end())
				key = _header.at(f).name;
			if (key == "")
				continue;
			std::string value = "";
			if (_header.find(f) != _header.end())
				value = _header.at(f).value;
			res += key + value + httpConstants::FIELD_BREAK;
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		res = "";
	}
	return res;
}

/* ************************************************************************** */
