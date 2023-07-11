
#ifndef H_T_T_P_REQUEST_HANDLER_HPP
#define H_T_T_P_REQUEST_HANDLER_HPP

#include <iostream>
#include <string>
#include <AllowedMethods/AllowedMethods.hpp>

namespace HTTPRequestHandler
{
	IAllowedMethods::type getRequestType(std::string request);

	std::string GET(std::string request);
	std::string POST(std::string request);
	std::string DELETE(std::string request);
	std::string UNKNOWN(std::string request);
};

#endif /* H_T_T_P_REQUEST_HANDLER_HPP */
