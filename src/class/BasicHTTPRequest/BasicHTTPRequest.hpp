
#ifndef BASIC_H_T_T_P_REQUEST_HPP
#define BASIC_H_T_T_P_REQUEST_HPP

#include <iostream>
#include <map>
#include <string>

#include <Path/Path.hpp>
#include <httpConstants/httpConstants.hpp>
#include <mapPrint/mapPrint.hpp>
#include <parser/parser.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class BasicHTTPRequest
{
  public:
	enum Type
	{
		GET,
		POST,
		DELETE,
	};
	enum HTTPVersion
	{
		UNKNOWN,
		HTTP_0_9,
		HTTP_1_0,
		HTTP_1_1,
		HTTP_2_0,
		HTTP_3,
	};

	class InvalidRequestException : public std::exception
	{
	  public:
		explicit InvalidRequestException(const std::string &msg);
		virtual ~InvalidRequestException() throw();
		virtual const char *what() const throw();

	  private:
		std::string _msg;
	};

	explicit BasicHTTPRequest(const std::string &raw_request);
	BasicHTTPRequest(const BasicHTTPRequest &src);
	~BasicHTTPRequest();

	BasicHTTPRequest &operator=(const BasicHTTPRequest &rhs);

	void setBody(void);

	const std::string &getRawRequest(void) const;
	Type getType(void) const;
	const std::string &getPath(void) const;
	const std::string &getQuery(void) const;
	HTTPVersion getHTTPVersion(void) const;
	const std::map<std::string, std::string> &getHeaders(void) const;
	const std::string &getBody(void) const;

  private:
	const std::string _raw;
	Type _type;
	Path _path;
	std::string _query;
	HTTPVersion _http_version;
	std::map<std::string, std::string> _headers;
	std::string _body;

	bool isChunked(void) const;

	static BasicHTTPRequest::Type _parseType(const std::string &raw_request);
	static Path _parsePath(const std::string &raw_request);
	static std::string _parseQuery(const std::string &raw_request);
	static HTTPVersion _parseHTTPVersion(const std::string &raw_request);
	static std::map<std::string, std::string> _parseHeaders(const std::string &raw_request);
	static bool _isKeyRestricted(const std::string &key);
};

std::ostream &operator<<(std::ostream &o, const BasicHTTPRequest &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* BASIC_H_T_T_P_REQUEST_HPP */
