
#include <HTTPRequestHandler/HTTPRequestHandler.hpp>

std::string HTTPRequestHandler::GET(Server server, BasicHTTPRequest basicRequest)
{
	(void)basicRequest;
	(void)server;
	return std::string("You sent a GET request:\n");
}

std::string HTTPRequestHandler::POST(Server server, BasicHTTPRequest basicRequest)
{
	(void)basicRequest;
	(void)server;
	return std::string("You sent a POST request:\n");
}

std::string HTTPRequestHandler::DELETE(Server server, BasicHTTPRequest basicRequest)
{
	(void)basicRequest;
	(void)server;
	return std::string("You sent a DELETE request:\n");
}

std::string HTTPRequestHandler::UNKNOWN(Server server, BasicHTTPRequest basicRequest)
{
	(void)basicRequest;
	(void)server;
	return std::string("You sent an UNKNOWN request:\n");
}