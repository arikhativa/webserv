
#include <HTTPCall/HTTPCall.hpp>
#include <HTTPRequestHandler/HTTPRequestHandler.hpp>

void HTTPRequestHandler::GET(HTTPCall &request)
{
	(void)request;
	request.setResponse("HTTP/1.1 200 OK\r\n\r\nYOU SENT A GET REQUEST");
}

void HTTPRequestHandler::POST(HTTPCall &request)
{
	(void)request;
	request.setResponse("HTTP/1.1 200 OK\r\n\r\nYOU SENT A POST REQUEST");
}

void HTTPRequestHandler::DELETE(HTTPCall &request)
{
	(void)request;
	request.setResponse("HTTP/1.1 200 OK\r\n\r\nYOU SENT A DELETE REQUEST");
}

void HTTPRequestHandler::UNKNOWN(HTTPCall &request)
{
	(void)request;
	request.setResponse("HTTP/1.1 200 OK\r\n\r\nYOU SENT A UNKNOWN REQUEST");
}