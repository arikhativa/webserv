#include <HTTPRequestHandler/HTTPRequestHandler.hpp>

bool	correctRequest(std::string request)
{
	size_t pos = 0;
	int i = 0;
	std::string key = "";
	std::string query = request.substr(0, request.find("\n"));
	while ((pos = query.find(" ")) != std::string::npos)
	{
		pos = query.find(" ");
		key = query.substr(0, pos);
		if (i == 0 && (key != "GET" && key != "POST" && key != "DELETE"))
		{
			ILogger::consoleLogDebug("Bad method");
			return (false);
		}
		if (i == 1 && key[0] != '/')
		{
			ILogger::consoleLogDebug("Bad path");
			return (false);
		}
		query = query.substr(pos + 1);
		i++;
	}
	if (query != "")
	{
		key = query.substr(0, query.find("\r"));
		if (i == 2 && (key != "HTTP/1.1" && key != "HTTP/1.0"))
		{
			ILogger::consoleLogDebug("Bad HTTP version");
			return (false);
		}
		i++;
	}
	if (i != 3)
	{
		ILogger::consoleLogDebug("Not 3 arguments");
		return (false);
	}
	
	std::vector<std::string> keys;
	std::vector<std::string> values;
	size_t limit = request.find("\r\n\r\n");
	query = request.substr(request.find("\n") + 1, limit);
	while ((pos = query.find("\r\n")) != std::string::npos)
	{
		pos = query.find("\n");
		key = query.substr(0, pos);
		std::size_t pos2 = key.find(":");
		if (pos2 != std::string::npos)
		{
			values.push_back( key.substr(pos2 + 1));
			keys.push_back(key.substr(0, pos2));
		}
		if (query.length() <= pos + 1)
			break;
		query = query.substr(pos + 1);
	}
	for (size_t j = 0; j < keys.size(); ++j) 
	{
		for (size_t k = 0; k < keys.size(); ++k) 
		{
			if (j != k && keys[j] == keys[k])
			{
				ILogger::consoleLogDebug("Repeated header");
				return (false);
			}
		}
		if (keys[j].length() > 4096 || values[j].size() > 4096)
		{
			ILogger::consoleLogDebug("Header too long");
			return (false);
		}
	}
	return (true);
}

void	correctRequestSize(std::string request, std::string body)
{
	std::size_t pos = request.find("Content-Length: ");
	if (pos != std::string::npos)
	{
		std::size_t pos2 = request.find("\r\n", pos);
		if (pos2 != std::string::npos)
		{
			std::string content_length = request.substr(pos + 16, pos2 - pos - 16);
			if (content_length != (body.length() + ""))
				throw HTTPRequestHandler::SizeError();
		}
	}
}

std::string HTTPRequestHandler::get::GET(Server server, std::string request)
{
	try
	{
		(void)server;
		std::string path = "/home/rufo/Desktop/42/"; //temporal, server.getPath();
		//TODO
		if (correctRequest(request) == false)
		{
			ILogger::consoleLogDebug("Bad request");
			ResponseHeader response(400);
			return (response.getResponse());
		}
		std::string file = httprequesthandlerGET::getQuery(request);
		if (httprequesthandlerGET::is_directory(path + file))
		{
			ILogger::consoleLogDebug("Is directory(" + path + file + ")");
			ResponseHeader response(200);
			if (file[file.length() - 1] != '/')
				file += "/";
			response.setContentType(".html");
			response.setBody(httprequesthandlerGET::getDirecoryContent(path, file));
			return (response.getResponse());
		}
		else if (httprequesthandlerGET::exists_file(path + file))
		{
			ILogger::consoleLogDebug("Is file(" + path + file + ")");
			ResponseHeader response(200);
			response.setBody(httprequesthandlerGET::getFileContent(path + file, server, request, response));
			return (response.getResponse());
		}
		else
		{
			ILogger::consoleLogDebug("Not found(" + path + file + ")");
			ResponseHeader response(404);
			return (response.getResponse());
		}
	}
	catch(const std::exception& e)
	{
		ILogger::consoleLogError("Error: " + std::string(e.what()));
		ResponseHeader errorResponse(500);
		return (errorResponse.getResponse());
	}
}

std::string HTTPRequestHandler::post::POST(Server server, std::string request)
{
	try
	{
		(void)server;
		if (correctRequest(request) == false)
		{
			ILogger::consoleLogDebug("Bad request, 400");
			ResponseHeader response(400);
			return (response.getResponse());
		}
		std::string path = "/home/rufo/Desktop/42/"; //temporal, server.getPath();
		
		std::string file = httprequesthandlerPOST::getQuery(request);
		if (!httprequesthandlerPOST::exists_file(path + file))
		{
			ILogger::consoleLogDebug("POST Not found(" + path + file + ") (404)");
			ResponseHeader response(404);
			return (response.getResponse());
		}
		if (httprequesthandlerPOST::is_directory(path + file))
		{
			ILogger::consoleLogDebug("Is directory(" + path + file + ")");
			ResponseHeader response(200);
			if (file[file.length() - 1] != '/')
				file += "/";
			response.setContentType(".html");
			response.setBody(httprequesthandlerGET::getDirecoryContent(path, file));//TODO: POST
			return (response.getResponse());
		}
		
		//contenido del fichero
		ILogger::consoleLogDebug("POST file(" + path + file + ")");
		ResponseHeader response(200);
		response.setBody(httprequesthandlerPOST::getFileContent(path + file, server, request, response));
		
		return (response.getResponse());

		/*
		std::string body = httprequesthandlerPOST::getBody(request);
		std::string nameFile = httprequesthandlerPOST::getNameFilePost(body);
		std::string args = httprequesthandlerPOST::getQueryCGIArgs(request);
		correctRequestSize(request, body);
		*/
	}
	catch(const HTTPRequestHandler::SizeError& e)
	{
		ILogger::consoleLogError("Error: " + std::string(e.what()));
		ResponseHeader errorResponse(400);
		return (errorResponse.getResponse());
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
	if (correctRequest(request) == false)
	{
		ILogger::consoleLogDebug("Bad request");
		ResponseHeader response(400);
		return (response.getResponse());
	}
	std::string path = "/home/rufo/Desktop/42/"; //temporal, server.getPath();
	
	std::string file = "";
	std::size_t barra_pos = request.find("/");
	if (barra_pos != std::string::npos)
	{
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
	//TODO temporal, must use the server config
		response.setConnection("GET, POST, DELETE");
	return (response.getResponse());
}