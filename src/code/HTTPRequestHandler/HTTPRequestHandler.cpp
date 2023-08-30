
#include <HTTPRequest/HTTPRequest.hpp>
#include <HTTPRequestHandler/HTTPRequestHandler.hpp>

void HTTPRequestHandler::GET(HTTPRequest &request)
{
	(void)request;
	request.setResponse("HTTP/1.1 200 OK\r\n\r\nYOU SENT A GET REQUEST");
}

void HTTPRequestHandler::POST(HTTPRequest &request)
{
	(void)request;
	request.setResponse("HTTP/1.1 200 OK\r\n\r\nYOU SENT A POST REQUEST");
}

void HTTPRequestHandler::DELETE(HTTPRequest &request)
{
	(void)request;
	request.setResponse("HTTP/1.1 200 OK\r\n\r\nYOU SENT A DELETE REQUEST");
}

void HTTPRequestHandler::UNKNOWN(HTTPRequest &request)
{
	(void)request;
	request.setResponse("HTTP/1.1 200 OK\r\n\r\nYOU SENT A UNKNOWN REQUEST");
}