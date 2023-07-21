
#ifndef RESPONSE_HEADER_HPP
#define RESPONSE_HEADER_HPP

#include <iostream>
#include <string>
#include <ctime>
#include <map>
#include <IStatusCodes/IStatusCodes.hpp>
#include <IContentTypes/IContentTypes.hpp>
#include <sstream>
#include <cstdlib>
#include <limits>
#include <ILogger/ILogger.hpp>
#include <iomanip>
#include <cstring>
#include <sys/time.h>
#include <time.h>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class ResponseHeader 
{
	struct HeaderFields
	{
		std::string name;
		std::string value;
	};

  public:
	explicit ResponseHeader(int code);
	ResponseHeader(ResponseHeader const &src);
	~ResponseHeader();
	ResponseHeader &operator=(ResponseHeader const &rhs);
	
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

	void		setStatusCode(int code);
	void		setContentType(std::string type);
	void		setContentLength(int lenght);
	void		setConnection(std::string connection);
	void		setBody(std::string body);
	std::string	getStatusMessage();
	std::string	getContentType();
	std::string	getResponse() ;
	std::string	getConnection() ;
	std::map<ResponseHeader::field, ResponseHeader::HeaderFields> getHeader() const;
  private:
	std::string	defaultErrorPage(int code);
	void		NotFound();
	void		MethodNotAllowed();
	void		defaultConstructor();
	std::string	getCurrentDate();
	std::map<ResponseHeader::field, ResponseHeader::HeaderFields> _header;
};
std::ostream &operator<<(std::ostream &o, ResponseHeader const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* RESPONSE_HEADER_HPP */
