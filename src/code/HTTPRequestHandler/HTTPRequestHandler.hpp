
#ifndef H_T_T_P_REQUEST_HANDLER_HPP
#define H_T_T_P_REQUEST_HANDLER_HPP

#include <BasicHTTPRequest/BasicHTTPRequest.hpp>
#include <Server/Server.hpp>
#include <httpRequestHandlerGET/httpRequestHandlerGET.hpp>
#include <matcher/matcher.hpp>

#include <iostream>
#include <string>

class HTTPCall;

namespace HTTPRequestHandler
{
	void GET(HTTPCall &request);
	void POST(HTTPCall &request);
	void DELETE(HTTPCall &request);
	void UNKNOWN(HTTPCall &request);
}; // namespace HTTPRequestHandler

#endif /* H_T_T_P_REQUEST_HANDLER_HPP */
