#include <HTTPRequestHandlerGET/HTTPRequestHandlerGET.hpp>

bool httprequesthandlerGET::isFileExists(const std::string &path)
{
	return (FileManager::isFileExists(path));
}

bool httprequesthandlerGET::isDirectory(const std::string &path)
{
	return (FileManager::isDirectory(path));
}

std::string httprequesthandlerGET::getFileContent(const std::string &path, Server server, BasicHTTPRequest basicRequest,
												  ResponseHeader &response)
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

			Path serverPath(".");
			return (obj1.executeCgiManager(serverPath));
		}
	}
	std::string content = FileManager::getFileContent(path);
	if (path.find(".") != std::string::npos)
		response.setContentType(path.substr(path.find_last_of(".")));
	return (content);
}

std::string httprequesthandlerGET::getDirecoryContent(const std::string &path, const std::string &name)
{
	return (FileManager::getDirectoryPreview(path, name));
}

const char *httprequesthandlerGET::cgiGETException::what() const throw()
{
	return "Error In cgi";
}
