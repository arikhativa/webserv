
#ifndef RESPONSE_HEADER_HPP
#define RESPONSE_HEADER_HPP

#include <HTTPStatusCode/HTTPStatusCode.hpp>
#include <ContentTypes/ContentTypes.hpp>
#include <converter/converter.hpp>
#include <ErrorPage/ErrorPage.hpp>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <sys/time.h>
#include <time.h>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class ResponseHeader
{

  public:
	enum field
	{
		STANDARD,
		SERVER,
		DATE,
		CONNECTION_TYPE,
		CONTENT_LENGHT,
		CONNECTION,
		BODY,
	};
	struct HeaderFields
	{
		std::string name;
		std::string value;
	};
	explicit ResponseHeader(int code, const ErrorPage &default_page);
	ResponseHeader(ResponseHeader const &src);
	~ResponseHeader();
	ResponseHeader &operator=(ResponseHeader const &rhs);
	void setStatusCode(int code);
	void setContentType(std::string type);
	void setConnection(std::string connection);
	void setBody(std::string body);
	std::string getStatusMessage();
	std::string getContentType();
	std::string getBody();
	std::string getResponse() const;
	std::string getConnection();
	std::map<ResponseHeader::field, ResponseHeader::HeaderFields> getHeader() const;

	class InvalidDefaultPage : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

  private:
	void setContentLength(int lenght);
	void defaultErrorPage(int code, const ErrorPage &default_page);
	void defaultConstructor();
	std::string getCurrentDate();
	std::map<ResponseHeader::field, ResponseHeader::HeaderFields> _header;
};
std::ostream &operator<<(std::ostream &o, ResponseHeader const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* RESPONSE_HEADER_HPP */
