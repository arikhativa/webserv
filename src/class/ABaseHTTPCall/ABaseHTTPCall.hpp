
#ifndef A_BASE_H_T_T_P_CALL_HPP
#define A_BASE_H_T_T_P_CALL_HPP

#include <iostream>
#include <map>
#include <string>

#include <converter/converter.hpp>
#include <httpConstants/httpConstants.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class ABaseHTTPCall
{
  public:
	enum HTTPVersion
	{
		UNKNOWN,
		HTTP_0_9,
		HTTP_1_0,
		HTTP_1_1,
		HTTP_2_0,
		HTTP_3_0,
	};

	explicit ABaseHTTPCall(const std::string &raw);
	ABaseHTTPCall(const ABaseHTTPCall &src);
	virtual ~ABaseHTTPCall();

	class Incomplete : public std::exception
	{
	  public:
		explicit Incomplete(const std::string &msg);
		virtual ~Incomplete() throw();
		virtual const char *what() const throw();

	  private:
		std::string _msg;
	};

	class Invalid : public std::exception
	{
	  public:
		explicit Invalid(const std::string &msg);
		virtual ~Invalid() throw();
		virtual const char *what() const throw();

	  private:
		std::string _msg;
	};

	ABaseHTTPCall &operator=(const ABaseHTTPCall &rhs);

	virtual void parseRaw(void) = 0;
	virtual std::string toString(void) const = 0;
	virtual void unParse(void);
	void parseBody(void);

	static std::string toStringVersion(HTTPVersion);

	const std::string &getRawRequest(void) const;
	const std::string &getLastExtention(void) const;
	HTTPVersion getHTTPVersion(void) const;
	const std::map< std::string, std::string > &getHeaders(void) const;
	const std::string &getBody(void) const;
	std::string getRawBody(void) const;
	std::string getRawHeader(void) const;
	bool isChunked(void) const;
	bool isBody(void) const;
	void extenedRaw(const std::string &raw);
	static bool isKeyRestricted(const std::string &key);

  protected:
	void _parseHTTPVersion(void);
	void _parseHeaders(void);

	std::string _raw;
	std::map< std::string, std::string > _headers;
	HTTPVersion _http_version;
	std::string _body;
	std::string _last_extention;

  private:
	void _parseBodyByChunked(void);
	void _parseBodyByContentLength(void);
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* A_BASE_H_T_T_P_CALL_HPP */
