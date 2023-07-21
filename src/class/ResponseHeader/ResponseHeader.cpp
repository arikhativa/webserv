
#include <ResponseHeader/ResponseHeader.hpp>


/*	
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ResponseHeader::ResponseHeader(int code)
{
	defaultConstructor();
	setStatusCode(code);
	if (code == 408 || code == 503)
		setConnection("close");
	if (code == 405)
		MethodNotAllowed();
	if (code == 404)
		NotFound();
	if (code == 500)
	{
		setContentType(".html");
		_header[CONNECTION].value = "close";
		setBody(defaultErrorPage(code));
	}
	
}

ResponseHeader::ResponseHeader(const ResponseHeader &src)
	: _header(src.getHeader())
{
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
	(void)i;
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string ResponseHeader::defaultErrorPage(int code)
{
	//TODO : use a template file if it is defined in the config file
	if (1==2)
	{
		return ("TODO");
	}
	else
	{
		std::stringstream number;
		number << code;
		return ("<!DOCTYPE html>\n<html>\n<body>\n<h1>" + number.str() + " " + IStatusCodes::_status_codes[code] + "</h1>\n</body>\n</html>");
	}
}

std::string	ResponseHeader::getCurrentDate(void)
{
	//TODO temporal format: [2023-07-21  11:28:33] GMT
	std::string formattedDate ="";
	_header[DATE].name = "";

    return formattedDate;
}

void	ResponseHeader::setStatusCode(int code)
{
	std::string			message;
	std::stringstream	number;

	number << code;
	message = IStatusCodes::_status_codes[code];
	if (message == "")
		throw std::runtime_error("Invalid status code");
	this->_header.at(STANDARD).value = number.str() + " " + message;
}

void	ResponseHeader::setContentType(std::string type) 
{
	this->_header.at(CONNECTION_TYPE).value = IContentTypes::_content_types[type];	
}

void	ResponseHeader::setContentLength(int lenght)
{
	std::ostringstream	number;

	number<<lenght;
	this->_header.at(CONTENT_LENGHT).value = number.str();
}

void	ResponseHeader::setConnection(std::string connection)
{
	this->_header.at(CONNECTION).value = connection;
}

void	ResponseHeader::setBody(std::string body)
{
	if (body.length() > std::numeric_limits<long unsigned int>::max())
	{
		setStatusCode(413);
		body  = defaultErrorPage(413);
	}
	this->_header[BODY].value = body;
	if (body.length() == 0)
		setContentLength(0);
	else
		setContentLength(body.length() + 1);
}

std::string ResponseHeader::getStatusMessage()
{
	return (this->_header.at(STANDARD).value);
}

std::string ResponseHeader::getContentType()
{
	return (this->_header.at(CONNECTION_TYPE).value);
}

std::string ResponseHeader::getConnection() 
{
	return (this->_header.at(CONNECTION).value);
}	

std::map<ResponseHeader::field, ResponseHeader::HeaderFields>	ResponseHeader::getHeader() const
{
	return (_header);
}

void	ResponseHeader::MethodNotAllowed()
{
	setContentType(".html");
	_header[CONNECTION].name = "Allow: ";
	setBody(defaultErrorPage(405));
}

void	ResponseHeader::NotFound()
{
	setContentType(".html");
	_header[CONNECTION].value = "close";
	setBody(defaultErrorPage(404));
}

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
	//_header[DATE].name = "Date: ";
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
std::string ResponseHeader::getResponse()
{
    std::string res = "";
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
    return res;
}

/* ************************************************************************** */
