
#ifndef H_T_T_P_REQUEST_HPP
#define H_T_T_P_REQUEST_HPP

#include <iostream>
#include <string>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class HTTPRequest
{
  public:
	explicit HTTPRequest(std::string rawRequest);
	HTTPRequest(HTTPRequest const &src);
	~HTTPRequest();

	HTTPRequest &operator=(HTTPRequest const &rhs);

	std::string getRawRequest(void) const;

  private:
	std::string _rawRequest;
};

std::ostream &operator<<(std::ostream &o, HTTPRequest const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* H_T_T_P_REQUEST_HPP */
