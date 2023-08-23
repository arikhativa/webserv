
#ifndef H_T_T_P_REQUEST_HANDLER_HPP
#define H_T_T_P_REQUEST_HANDLER_HPP

#include <BasicHTTPRequest/BasicHTTPRequest.hpp>
#include <Server/Server.hpp>
#include <iostream>
#include <string>

namespace HTTPRequestHandler
{
	std::string GET(Server server, BasicHTTPRequest basicRequest);
	std::string POST(Server server, BasicHTTPRequest basicRequest);
	std::string DELETE(Server server, BasicHTTPRequest basicRequest);
	std::string UNKNOWN(Server server, BasicHTTPRequest basicRequest);
}; // namespace HTTPRequestHandler

#endif /* H_T_T_P_REQUEST_HANDLER_HPP */
