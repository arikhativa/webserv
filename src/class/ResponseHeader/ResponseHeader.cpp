
#include <ResponseHeader/ResponseHeader.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ResponseHeader::ResponseHeader(int code, const ErrorPage &default_page)
{
	defaultConstructor();
	setStatusCode(code);
	if (code >= 400)
	{
		setContentType(".html");
		setConnection("close");
		defaultErrorPage(code, default_page);
		if (code == 405)
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

void ResponseHeader::defaultConstructor()
{

	for (field f = STANDARD; f <= BODY; f = static_cast<field>(static_cast<int>(f) + 1))
	{
		HeaderFields defaultHeader;
		_header.insert(std::make_pair(f, defaultHeader));
	}
	_header[STANDARD].name = "HTTP/1.1 ";
	_header[STANDARD].value = "";
	_header[SERVER].name = "Server: ";
	_header[SERVER].value = "webserv";
	_header[DATE].name = "Date: ";
	_header[DATE].value = getCurrentDate();
	_header[CONNECTION_TYPE].name = "Content-Type: ";
	_header[CONNECTION_TYPE].value = "";
	_header[CONTENT_LENGHT].name = "Content-Length: ";
	_header[CONTENT_LENGHT].value = "";
	_header[CONNECTION].name = "Connection: ";
	_header[BODY].name = "\r\n";
	_header[BODY].value = "";
	setContentType(".txt");
	setContentLength(0);
	setConnection("keep-alive");
}

void ResponseHeader::defaultErrorPage(int code, const ErrorPage &default_page)
{
	HTTPStatusCode default_code = default_page.getStatus();
	if (code == default_code.get())
	{
		std::string path = default_page.getPath().get();
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
		setBody("<!DOCTYPE html>\n<html>\n<body>\n<h1>" + converter::numToString(code) + " " +
					HTTPStatusCode(code).toString() + "</h1>\n</body>\n</html>");
}

std::string ResponseHeader::getCurrentDate(void)
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

void ResponseHeader::setContentLength(int lenght)
{
	this->_header.at(CONTENT_LENGHT).value = converter::numToString(lenght);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

void ResponseHeader::setStatusCode(int code)
{
	std::string message;

	message = HTTPStatusCode(code).toString();
	if (message == "")
		throw std::runtime_error("Invalid status code");
	std::string value = converter::numToString(code) + " " + message;
	this->_header.at(STANDARD).value = value;
}

void ResponseHeader::setContentType(std::string type)
{
	if (type == "")
		type = "text/plain";
	ContentTypes contentType(type);
	this->_header.at(CONNECTION_TYPE).value = contentType.get();
}

void ResponseHeader::setConnection(std::string connection)
{
	this->_header.at(CONNECTION).value = connection;
}

void ResponseHeader::setBody(std::string body)
{
	
	this->_header[BODY].value = body;
	int lenght = body.length();
	if (lenght == 0)
		setContentLength(lenght);
	else
		setContentLength(lenght + 1);
	if (this->_header.at(CONNECTION_TYPE).value == "")
		setContentType(".html");
}

std::string ResponseHeader::getStatusMessage()
{
	return (this->_header.at(STANDARD).value);
}

std::string ResponseHeader::getContentType()
{
	return (this->_header.at(CONNECTION_TYPE).value);
}

std::string ResponseHeader::getBody()
{
	return (this->_header.at(BODY).value);
}

std::string ResponseHeader::getConnection()
{
	return (this->_header.at(CONNECTION).value);
}

std::map<ResponseHeader::field, ResponseHeader::HeaderFields> ResponseHeader::getHeader() const
{
	return (_header);
}

std::string ResponseHeader::getResponse() const
{
	std::string res = "";
	try
	{
		size_t totalSize = 0;
		for (field f = STANDARD; f <= BODY; f = static_cast<field>(static_cast<int>(f) + 1))
			totalSize += _header.at(f).name.length() + _header.at(f).value.length() + 10;
		res.reserve(totalSize);
		for (field f = STANDARD; f <= BODY; f = static_cast<field>(static_cast<int>(f) + 1))
		{
			std::string key = "";
			if (_header.find(f) != _header.end())
				key = _header.at(f).name;
			if (key == "")
				continue;
			std::string value = "";
			if (_header.find(f) != _header.end())
				value = _header.at(f).value;
			res += key + value + "\n";
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
