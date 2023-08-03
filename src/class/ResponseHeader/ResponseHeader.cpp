
#include <ResponseHeader/ResponseHeader.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ResponseHeader::ResponseHeader(HTTPStatusCode code, std::list<const ErrorPage *> error_pages)
{
	_defaultConstructor();
	setStatusCode(code);
	if (_isErrorCode(code))
	{
		setContentType(HTML_SUFFIX);
		setConnection(CONNECTION_CLOSE);
		_setErrorPageIfNeeded(code, error_pages);
		if (code.get() == 405)
			_header[CONNECTION].name = "Allow: ";
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
	_header[STANDARD].name = HTTP_VERSION;
	_header[STANDARD].value = "";
	_header[SERVER].name = SERVER_FIELD_KEY;
	_header[SERVER].value = SERVER_FIELD_VALUE;
	_header[DATE].name = DATE_FIELD_KEY;
	_header[DATE].value = _getCurrentDate();
	_header[CONNECTION_TYPE].name = CONTENT_TYPE_FIELD_KEY;
	_header[CONNECTION_TYPE].value = "";
	_header[CONTENT_LENGHT].name = CONTENT_LENGHT_FIELD_KEY;
	_header[CONTENT_LENGHT].value = "";
	_header[CONNECTION].name = CONNECTION_FIELD_KEY;
	_header[BODY].name = FIELD_BREAK;
	_header[BODY].value = "";
	setContentType(TXT_SUFFIX);
	_setContentLength(0);
	setConnection(CONNECTION_ALIVE);
}

void ResponseHeader::_setErrorPageIfNeeded(HTTPStatusCode code, std::list<const ErrorPage *> error_pages)
{
	std::list<const ErrorPage *>::iterator it = error_pages.begin();
	while (it != error_pages.end())
	{
		if ((*it)->getStatus().get() == code.get())
			break;
		++it;
	}
	if (it != error_pages.end())
	{
		std::string path = (*it)->getPath().get();
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
		setBody("<!DOCTYPE html>\n<html>\n<body>\n<h1>" + converter::numToString(code.get()) + " " + code.toString() +
				"</h1>\n</body>\n</html>");
}

const std::string ResponseHeader::_getCurrentDate(void)
{
	char buffer[80];
	std::time_t now;
	struct std::tm *timeinfo;
	std::string result = "";
	now = std::time(0);
	timeinfo = std::gmtime(&now);
	std::strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", timeinfo);
	result.reserve(80);
	result = buffer;
	return (result);
}

void ResponseHeader::_setContentLength(size_t lenght)
{
	this->_header.at(CONTENT_LENGHT).value = converter::numToString(lenght);
}

bool ResponseHeader::_isErrorCode(HTTPStatusCode code)
{
	return (code.get() >= 400);
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
	std::string value = converter::numToString(code.get()) + " " + code.toString();
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
	int lenght = body.length();
	if (lenght == 0)
		_setContentLength(lenght);
	else
		_setContentLength(lenght + 1);
	if (this->_header.at(CONNECTION_TYPE).value == "")
		setContentType(HTML_SUFFIX);
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
			res += key + value + FIELD_BREAK;
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
