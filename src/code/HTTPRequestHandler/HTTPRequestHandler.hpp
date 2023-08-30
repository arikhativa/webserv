
#ifndef H_T_T_P_REQUEST_HANDLER_HPP
#define H_T_T_P_REQUEST_HANDLER_HPP

#include <BasicHTTPRequest/BasicHTTPRequest.hpp>
#include <Server/Server.hpp>
#include <iostream>
#include <string>

class HTTPRequest;

namespace HTTPRequestHandler
{
	void GET(HTTPRequest &request);
	void POST(HTTPRequest &request);
	void DELETE(HTTPRequest &request);
	void UNKNOWN(HTTPRequest &request);
}; // namespace HTTPRequestHandler

#endif /* H_T_T_P_REQUEST_HANDLER_HPP */
