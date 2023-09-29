
#ifndef RESPONSE_HEADER_HPP
#define RESPONSE_HEADER_HPP

#include <ContentTypes/ContentTypes.hpp>
#include <ErrorPage/ErrorPage.hpp>
#include <ErrorPageSet/ErrorPageSet.hpp>
#include <HTTPStatusCode/HTTPStatusCode.hpp>
#include <IErrorPage/IErrorPage.hpp>
#include <converter/converter.hpp>
#include <httpConstants/httpConstants.hpp>

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

class ResponseHeader
{

  public:
	enum field_key
	{
		STANDARD,
		SERVER,
		DATE,
		CONNECTION_TYPE,
		CONTENT_LENGTH,
		CONNECTION,
		LOCATION,
		BODY,
	};
	struct Field
	{
		std::string name;
		std::string value;
	};
	ResponseHeader(HTTPStatusCode code, const ErrorPageSet &error_page_set);
	ResponseHeader(ResponseHeader const &src);
	~ResponseHeader();
	ResponseHeader &operator=(ResponseHeader const &rhs);
	void setStatusCode(HTTPStatusCode code);
	void setContentType(const std::string &type);
	void setConnection(const std::string &connection);
	void setBody(const std::string &body);
	void setHeader(const std::string &key, const std::string &value);
	void setLocationHeader(const std::string &value);
	const std::string getStatusMessage(void);
	const std::string getContentType(void);
	const std::string getBody(void);
	const std::string getResponse(void) const;
	const std::string getConnection(void);
	size_t _getTotalSize(void) const;
	const std::map< ResponseHeader::field_key, ResponseHeader::Field > getHeader() const;

	class InvalidDefaultPage : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

  private:
	void _setContentLength(size_t length);
	void _setErrorPageIfNeeded(HTTPStatusCode code, const ErrorPageSet &error_page_set);
	void _defaultConstructor();
	const std::string _getCurrentDate();
	bool _isErrorCode(HTTPStatusCode code);
	std::map< ResponseHeader::field_key, ResponseHeader::Field > _header;
};
std::ostream &operator<<(std::ostream &o, ResponseHeader const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* RESPONSE_HEADER_HPP */
