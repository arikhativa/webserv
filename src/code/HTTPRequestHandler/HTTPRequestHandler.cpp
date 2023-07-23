
#include <HTTPRequestHandler/HTTPRequestHandler.hpp>

std::string HTTPRequestHandler::get::GET(Server server, std::string request)
{
	(void)request;
	(void)server;
	return std::string("You sent a GET request:\n");
}

std::string HTTPRequestHandler::post::POST(Server server, std::string request)
{
	try
	{
		(void)server;
		std::string path = "/home/rufo/Desktop/42/web_example/"; //temporal, server.getPath();
		{
			std::size_t pos = request.find("\r\n");
			if (pos != std::string::npos)
				ILogger::consoleLogDebug("POST request: " + request.substr(0, pos));
			else
				ILogger::consoleLogDebug("POST request: " + request);
		}
		std::string file = httprequesthandlerPOST::getQuery(request);
		if (!httprequesthandlerPOST::exists_file(path + file))
		{
			ILogger::consoleLogDebug("POST Not found(" + path + file + ")");
			ResponseHeader response(404);
			ILogger::consoleLogDebug("POST status code 404");
			return (response.getResponse());
		}
		std::string body = httprequesthandlerPOST::getBody(request);
		std::string nameFile = httprequesthandlerPOST::getNameFilePost(body);
		if (nameFile == "")
		{
			ResponseHeader errorResponse(204);
			errorResponse.setBody("");
			ILogger::consoleLogDebug("POST status code 204");
			return (errorResponse.getResponse());
		}
		std::string contentFile = httprequesthandlerPOST::getContentFilePost(body);
		std::ofstream outfile ((path + nameFile).c_str());
		outfile << contentFile;
		outfile.close();
		ResponseHeader response(201);
		ILogger::consoleLogDebug("POST status code 201");
		response.setContentType(".html");
		response.setBody("<html>\n<body>\n<h1>File uploaded</h1>\n</body>\n</html>");
		return (response.getResponse());
	}
	catch(const std::exception& e)
	{
		ILogger::consoleLogError("Error: " + std::string(e.what()));
		ResponseHeader errorResponse(500);
		return (errorResponse.getResponse());
	}
}

std::string HTTPRequestHandler::delete_::DELETE(Server server, std::string request)
{
	(void)server;
	std::string path = "/home/rufo/Desktop/42/web_example/"; //temporal, server.getPath();
	{
		std::size_t pos = request.find("\r\n");
		if (pos != std::string::npos)
			ILogger::consoleLogDebug("POST request: " + request.substr(0, pos));
		else
			ILogger::consoleLogDebug("POST request: " + request);
	}
	std::string file = "";
	std::size_t barra_pos = request.find("/");
	if (barra_pos != std::string::npos) {
		std::size_t espacio_pos = request.find(" ", barra_pos);
		if (espacio_pos != std::string::npos) 
			 file = request.substr(barra_pos + 1, espacio_pos - barra_pos - 1);
	}
	if (!httprequesthandlerDELETE::exists_file(path + file))
	{
		ILogger::consoleLogDebug("DELETE file not found(" + path + file + ")");
		ResponseHeader response(404);
		return (response.getResponse());
	}
	std::remove((path + file).c_str());
	ILogger::consoleLogDebug("DELETE file deleted(" + path + file + ")");
	ResponseHeader response(200);
	response.setBody("<!DOCTYPE html>\n<html>\n<body>\n<h1>File deleted</h1>\n</body>\n</html>");
	response.setContentType(".html");
	return (response.getResponse());
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