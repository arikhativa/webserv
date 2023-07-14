
#include <HTTPRequestHandler/HTTPRequestHandler.hpp>

std::string HTTPRequestHandler::GET(std::string request)
{
	(void)request;
	return std::string("You sent a GET request:\n");
}

std::string HTTPRequestHandler::POST(std::string request)
{
	(void)request;
	return std::string("You sent a POST request:\n");
}

std::string HTTPRequestHandler::DELETE(std::string request)
{
	(void)request;
	return std::string("You sent a DELETE request:\n");
}

std::string HTTPRequestHandler::UNKNOWN(std::string request)
{
	(void)request;
	return std::string("You sent an UNKNOWN request:\n");
}