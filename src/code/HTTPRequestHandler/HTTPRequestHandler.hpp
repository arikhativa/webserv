
#ifndef H_T_T_P_REQUEST_HANDLER_HPP
#define H_T_T_P_REQUEST_HANDLER_HPP

#include <iostream>
#include <string>
#include <Server/Server.hpp>

namespace HTTPRequestHandler
{
	std::string GET(Server server, std::string request);
	std::string POST(Server server, std::string request);
	std::string DELETE(Server server, std::string request);
	std::string UNKNOWN(Server server, std::string request);
};

#endif /* H_T_T_P_REQUEST_HANDLER_HPP */
