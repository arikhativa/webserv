
#ifndef H_T_T_P_REQUEST_HANDLER_HPP
#define H_T_T_P_REQUEST_HANDLER_HPP

#include <HTTPRequestHandlerDELETE/HTTPRequestHandlerDELETE.hpp>
#include <HTTPRequestHandlerGET/HTTPRequestHandlerGET.hpp>
#include <HTTPRequestHandlerPOST/HTTPRequestHandlerPOST.hpp>
#include <BasicHTTPRequest/BasicHTTPRequest.hpp>
#include <FileManager/FileManager.hpp>
#include <HTTPStatusCode/HTTPStatusCode.hpp>
#include <ResponseHeader/ResponseHeader.hpp>
//#include <ChunkManager/ChunkManager.hpp>
#include <Server/Server.hpp>
#include <PollManager/PollManager.hpp>

static const std::string HTTP_VERSION1_1 = "HTTP/1.1";
static const std::string HTTP_VERSION1_0 = "HTTP/1.0";
static const size_t MAX_HEADER_LENGHT = 4096;
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
		std::string UNKNOWN(Server server, BasicHTTPRequest request);
	}
	
}; // namespace HTTPRequestHandler

#endif /* H_T_T_P_REQUEST_HANDLER_HPP */
