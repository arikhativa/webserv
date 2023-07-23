
#include <HTTPRequestHandler/HTTPRequestHandler.hpp>

std::string HTTPRequestHandler::get::GET(Server server, std::string request)
{
	(void)request;
	(void)server;
	return std::string("You sent a GET request:\n");
}

std::string HTTPRequestHandler::post::POST(Server server, std::string request)
{
	(void)request;
	(void)server;
	return std::string("You sent a POST request:\n");
}

std::string HTTPRequestHandler::delete_::DELETE(Server server, std::string request)
{
	(void)request;
	(void)server;
	return std::string("You sent a DELETE request:\n");
}

std::string HTTPRequestHandler::unknown::UNKNOWN(Server server, std::string request)
{
	ILogger::consoleLogDebug("UNKNOWN request: " + request);
	(void)server;
	ResponseHeader response(405);
	//temporal, must use the server config
		response.setConnection("GET, POST, DELETE");
	return (response.getResponse());
}