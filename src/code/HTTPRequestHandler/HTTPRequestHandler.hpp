
#ifndef H_T_T_P_REQUEST_HANDLER_HPP
#define H_T_T_P_REQUEST_HANDLER_HPP

#include <iostream>

#include <Server/Server.hpp>
#include <ILogger/ILogger.hpp>
#include <HTTPRequestHandler/httprequesthandlerGET.hpp>
#include <HTTPRequestHandler/httprequesthandlerPOST.hpp>
#include <HTTPRequestHandler/httprequesthandlerDELETE.hpp>
#include <HTTPRequestHandler/httprequesthandlerUNKNOWN.hpp>
#include <ResponseHeader/ResponseHeader.hpp>

namespace HTTPRequestHandler 
{
	namespace get
	{
		std::string GET(Server server, std::string request);
	}
	namespace post
	{
		std::string POST(Server server, std::string request);
	}
	namespace delete_
	{
		std::string DELETE(Server server, std::string request);
	}
	namespace unknown
	{
		std::string UNKNOWN(Server server, std::string request);
	}
};

#endif /* H_T_T_P_REQUEST_HANDLER_HPP */
