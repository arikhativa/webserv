
#ifndef H_T_T_P_REQUEST_HANDLER_HPP
#define H_T_T_P_REQUEST_HANDLER_HPP

#include <BasicHTTPRequest/BasicHTTPRequest.hpp>
#include <FileManager/FileManager.hpp>
#include <HTTPRequestHandlerDELETE/HTTPRequestHandlerDELETE.hpp>
#include <HTTPRequestHandlerGET/HTTPRequestHandlerGET.hpp>
#include <HTTPRequestHandlerPOST/HTTPRequestHandlerPOST.hpp>
#include <HTTPStatusCode/HTTPStatusCode.hpp>
#include <ResponseHeader/ResponseHeader.hpp>
//#include <ChunkManager/ChunkManager.hpp>
#include "ServerConf/ServerConf.hpp"
#include <Path/Path.hpp>
#include <Server/Server.hpp>

namespace HTTPRequestHandler
{
	namespace get
	{
		std::string GET(Server server, BasicHTTPRequest request);
	}
	namespace post
	{
		std::string POST(Server server, BasicHTTPRequest request);
	}
	namespace delete_
	{
		std::string DELETE(Server server, BasicHTTPRequest request);
	}
	namespace unknown
	{
		std::string UNKNOWN(Server server);
	}

}; // namespace HTTPRequestHandler

#endif /* H_T_T_P_REQUEST_HANDLER_HPP */
