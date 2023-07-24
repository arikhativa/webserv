
#include <HTTPRequestHandler/HTTPRequestHandler.hpp>

std::string HTTPRequestHandler::get::GET(Server server, std::string request)
{
	try
	{
		(void)server;
		std::string path = "/home/rufo/Desktop/42/web_example/"; //temporal, server.getPath();
		{
			std::size_t pos = request.find("\r\n");
			if (pos != std::string::npos)
				ILogger::consoleLogDebug("GET request: " + std::string(request.substr(0, pos)));
			else
				ILogger::consoleLogDebug("GET request: " + request);
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
			if (file.find(".") != std::string::npos)
			{
				//!temporal
				std::map<std::string, std::string> cgi;//=server.get....();
				cgi[".py"] = "/usr/bin/python3";
				cgi[".php"] = "/usr/bin/php-cgi";


				if (cgi.find(file.substr(file.find_last_of("."))) != cgi.end())
					response.setContentType(".html");
				response.setContentType(file.substr(file.find_last_of(".")));
			}
			response.setBody(httprequesthandlerGET::getFileContent(path + file, server, request));
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
		std::string path = "/home/rufo/Desktop/42/web_example/"; //temporal, server.getPath();
		{
			std::size_t pos = request.find("\r\n");
			if (pos != std::string::npos)
				ILogger::consoleLogDebug("POST request: " + request.substr(0, pos));
			else
				ILogger::consoleLogDebug("POST request: " + request);
		}
		std::string file = httprequesthandlerPOST::getQuery(request);
		std::cout << "url: " << path + file << std::endl;
		if (!httprequesthandlerPOST::exists_file(path + file))
		{
			ILogger::consoleLogDebug("POST Not found(" + path + file + ")");
			ResponseHeader response(404);
			ILogger::consoleLogDebug("POST status code 404");
			return (response.getResponse());
		}
		if (httprequesthandlerPOST::is_directory(path + file))
		{
			ILogger::consoleLogDebug("POST directory(" + path + file + ")");
			ResponseHeader response(405);
			ILogger::consoleLogDebug("POST status code 405");
			return (response.getResponse());
		}
		std::string body = httprequesthandlerPOST::getBody(request);
		std::string nameFile = httprequesthandlerPOST::getNameFilePost(body);
		std::string args = httprequesthandlerPOST::getQueryCGIArgs(request);
		if ((nameFile == "" && args == "") || (nameFile == "" && args != ""))
		{
			ResponseHeader response(200);
			ILogger::consoleLogDebug("POST status code 200");
			response.setContentType(".html");
			response.setBody(httprequesthandlerPOST::getFileContent(path + file, server, request));
			return (response.getResponse());
		}
		if (httprequesthandlerPOST::exists_file(path + nameFile))
		{
			ResponseHeader response(409);
			ILogger::consoleLogDebug("POST status code 409");
			return (response.getResponse());
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