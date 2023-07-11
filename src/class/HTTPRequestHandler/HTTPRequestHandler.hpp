
#ifndef H_T_T_P_REQUEST_HANDLER_HPP
#define H_T_T_P_REQUEST_HANDLER_HPP

#include <iostream>
#include <string>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class HTTPRequestHandler
{
  public:
	HTTPRequestHandler();
	explicit HTTPRequestHandler(int i);
	HTTPRequestHandler(HTTPRequestHandler const &src);
	~HTTPRequestHandler();

	HTTPRequestHandler &operator=(HTTPRequestHandler const &rhs);

	// int getValue(void) const;

	static getType(std::string request);

  private:
	static AllowedMethods allowedMethods;
};

std::ostream &operator<<(std::ostream &o, HTTPRequestHandler const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* H_T_T_P_REQUEST_HANDLER_HPP */
