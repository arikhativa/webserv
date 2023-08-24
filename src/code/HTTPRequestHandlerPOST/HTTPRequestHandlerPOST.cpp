#include <HTTPRequestHandlerPOST/HTTPRequestHandlerPOST.hpp>

bool httprequesthandlerPOST::isFileExists(const std::string &path)
{
	return (FileManager::isFileExists(path));
}

bool httprequesthandlerPOST::isDirectory(const std::string &path)
{
	return (FileManager::isDirectory(path));
}

std::string httprequesthandlerPOST::getBody(std::string request)
{
	std::string body = "";
	std::size_t pos = request.find(httpConstants::HEADER_BREAK);
	if (pos != std::string::npos)
		body = request.substr(pos + 4);
	return (body);
}

std::string httprequesthandlerPOST::getContentFilePost(std::string body)
{
	std::string identificador = body.substr(0, body.find(httpConstants::FIELD_BREAK));
	std::string content = body.substr(body.find(identificador) + identificador.length() + 2);
	content = content.substr(0, content.find(identificador) - 2);
	content = content.substr(content.find(httpConstants::HEADER_BREAK) + 4);
	return (content);
}

std::string httprequesthandlerPOST::getFileContent(const std::string &path, Server server,
												   BasicHTTPRequest basicRequest, ResponseHeader &response)
{
	//! temporal
	std::map<std::string, std::string> cgi; //=server.get....();
	cgi[".py"] = "/usr/bin/python3";
	cgi[".php"] = "/usr/bin/php-cgi";
	cgi[".sh"] = "/usr/bin/sh";

	if (path.find(".") != std::string::npos)
	{
		std::string ext = path.substr(path.find_last_of("."));
		if (cgi.find(ext) != cgi.end())
		{
			(void)server;
			//! TODO: use server settings
			std::string serverName("serverName");
			std::string port("1234");

			Path pathCGI(cgi[ext]);
			CgiManager obj1(basicRequest, pathCGI, serverName, port);

			//! TODO: dont use pollmanager
			Path serverPath(".");
			return (obj1.executeCgiManager(serverPath));
		}
	}
	std::string content = FileManager::getFileContent(path);
	if (path.find(".") != std::string::npos)
		response.setContentType(path.substr(path.find_last_of(".")));
	return (content);
}
