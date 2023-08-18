
#ifndef H_T_T_P_RESPONSE_HPP
#define H_T_T_P_RESPONSE_HPP

#include <iostream>
#include <string>

#include <ABaseHTTPCall/ABaseHTTPCall.hpp>
#include <HTTPStatusCode/HTTPStatusCode.hpp>
#include <mapPrint/mapPrint.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class HTTPResponse : public ABaseHTTPCall
{
  public:
	explicit HTTPResponse(const std::string &raw);
	HTTPResponse(const HTTPResponse &src);
	virtual ~HTTPResponse();

	HTTPResponse &operator=(const HTTPResponse &rhs);

	virtual void parseRaw(void);
	virtual std::string toString(void) const;
	virtual void unParse(void);

	HTTPStatusCode getStatusCode(void) const;

  private:
	void _parseStatusLine(void);

	HTTPStatusCode _stt;
};

std::ostream &operator<<(std::ostream &o, const HTTPResponse &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* H_T_T_P_RESPONSE_HPP */
