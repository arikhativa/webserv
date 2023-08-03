
#ifndef RESPONSE_HEADER_HPP
#define RESPONSE_HEADER_HPP

#include <ContentTypes/ContentTypes.hpp>
#include <ErrorPage/ErrorPage.hpp>
#include <HTTPStatusCode/HTTPStatusCode.hpp>
#include <converter/converter.hpp>

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <sys/time.h>
#include <time.h>

#ifdef TEST_ON
#define private public
#define protected public
#endif

static const std::string HTML_SUFFIX = ".html";
static const std::string TXT_SUFFIX = ".txt";
static const std::string HTTP_VERSION = "HTTP/1.1 ";
static const std::string FIELD_BREAK = "\r\n";
static const std::string SERVER_FIELD_KEY = "Server: ";
static const std::string SERVER_FIELD_VALUE = "webserv";
static const std::string DATE_FIELD_KEY = "Date: ";
static const std::string CONTENT_TYPE_FIELD_KEY = "Content-Type: ";
static const std::string CONTENT_LENGHT_FIELD_KEY = "Content-Length: ";
static const std::string CONNECTION_FIELD_KEY = "Connection: ";
static const std::string CONNECTION_ALIVE = "keep-alive";
static const std::string CONNECTION_CLOSE = "close";

class ResponseHeader
{

  public:
	enum field_key
	{
		STANDARD,
		SERVER,
		DATE,
		CONNECTION_TYPE,
		CONTENT_LENGHT,
		CONNECTION,
		BODY,
	};
	struct Field
	{
		std::string name;
		std::string value;
	};
	explicit ResponseHeader(HTTPStatusCode code, std::list<const ErrorPage *> error_pages);
	ResponseHeader(ResponseHeader const &src);
	~ResponseHeader();
	ResponseHeader &operator=(ResponseHeader const &rhs);
	void setStatusCode(HTTPStatusCode code);
	void setContentType(const std::string &type);
	void setConnection(const std::string &connection);
	void setBody(const std::string &body);
	const std::string getStatusMessage(void);
	const std::string getContentType(void);
	const std::string getBody(void);
	const std::string getResponse(void) const;
	const std::string getConnection(void);
	size_t _getTotalSize(void) const;
	const std::map<ResponseHeader::field_key, ResponseHeader::Field> getHeader() const;

	class InvalidDefaultPage : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

  private:
	void _setContentLength(size_t lenght);
	void _setErrorPageIfNeeded(HTTPStatusCode code, std::list<const ErrorPage *> error_pages);
	void _defaultConstructor();
	const std::string _getCurrentDate();
	bool _isErrorCode(HTTPStatusCode code);
	std::map<ResponseHeader::field_key, ResponseHeader::Field> _header;
};
std::ostream &operator<<(std::ostream &o, ResponseHeader const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* RESPONSE_HEADER_HPP */
