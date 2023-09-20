
#ifndef H_T_T_P_STATUS_CODE_HPP
#define H_T_T_P_STATUS_CODE_HPP

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class HTTPStatusCode
{
  public:
	enum Code
	{
		// 1xx Informational
		CONTINUE = 100,
		SWITCHING_PROTOCOLS = 101,

		// 2xx Successful
		OK = 200,
		CREATED = 201,
		ACCEPTED = 202,
		NON_AUTHORITATIVE_INFORMATION = 203,
		NO_CONTENT = 204,
		RESET_CONTENT = 205,
		PARTIAL_CONTENT = 206,

		// 3xx Redirection
		MULTIPLE_CHOICES = 300,
		MOVED_PERMANENTLY = 301,
		FOUND = 302,
		SEE_OTHER = 303,
		NOT_MODIFIED = 304,
		USE_PROXY = 305,
		UNUSED = 306,
		TEMPORARY_REDIRECT = 307,

		// 4xx Client Error
		BAD_REQUEST = 400,
		UNAUTHORIZED = 401,
		PAYMENT_REQUIRED = 402,
		FORBIDDEN = 403,
		NOT_FOUND = 404,
		METHOD_NOT_ALLOWED = 405,
		NOT_ACCEPTABLE = 406,
		PROXY_AUTHENTICATION_REQUIRED = 407,
		REQUEST_TIMEOUT = 408,
		CONFLICT = 409,
		GONE = 410,
		LENGTH_REQUIRED = 411,
		PRECONDITION_FAILED = 412,
		REQUEST_ENTITY_TOO_LARGE = 413,
		REQUEST_URI_TOO_LONG = 414,
		UNSUPPORTED_MEDIA_TYPE = 415,
		REQUESTED_RANGE_NOT_SATISFIABLE = 416,
		EXPECTATION_FAILED = 417,

		// 5xx Server Error
		INTERNAL_SERVER_ERROR = 500,
		NOT_IMPLEMENTED = 501,
		BAD_GATEWAY = 502,
		SERVICE_UNAVAILABLE = 503,
		GATEWAY_TIMEOUT = 504,
		HTTP_VERSION_NOT_SUPPORTED = 505,
	};

	static bool isValid(int code);

	// object
	explicit HTTPStatusCode(const std::string &code);
	explicit HTTPStatusCode(int code);
	explicit HTTPStatusCode(HTTPStatusCode::Code code);
	HTTPStatusCode(HTTPStatusCode const &src);
	~HTTPStatusCode();

	HTTPStatusCode &operator=(HTTPStatusCode const &rhs);

	class InvalidStatusCodeException : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

	std::string toString(void) const;
	HTTPStatusCode::Code get(void) const;
	void set(HTTPStatusCode::Code code);
	void set(int code);
	void set(const std::string &code);

  private:
	static const std::map< HTTPStatusCode::Code, std::string > _map;

	HTTPStatusCode::Code _code;
};

std::ostream &operator<<(std::ostream &o, HTTPStatusCode const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* H_T_T_P_STATUS_CODE_HPP */
