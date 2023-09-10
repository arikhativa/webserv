#include <HTTPRequestHandlerGET/HTTPRequestHandlerGET.hpp>

bool httprequesthandlerGET::isFileExists(const std::string &path)
{
	return (FileManager::isFileExists(path));
}

bool httprequesthandlerGET::isDirectory(const std::string &path)
{
	return (FileManager::isDirectory(path));
}

std::string httprequesthandlerGET::getFileContent(const std::string &path, ResponseHeader &response,
												  HTTPRequest &request)
{
	// if (isCgi(void))
	//{
	Path pathCGI("/usr/bin/python3");
	std::string serverName = "";
	//! TODO revisar
	if (request.getSocket() == NULL)
		throw std::runtime_error("Error: socket is null");
	Port port = request.getSocket()->getPort();

	CgiManager obj1(request.getBasicRequest(), pathCGI, serverName, port.get() + "");
	return (obj1.executeCgiManager(request.getPathServerDirectory()));
	//}
	if (path.find(".") != std::string::npos)
		response.setContentType(path.substr(path.find_last_of(".")));
	return (FileManager::getFileContent(path));
}

std::string httprequesthandlerGET::getDirecoryContent(const Path &path, const Path &name)
{
	return (FileManager::getDirectoryPreview(path.get(), name.get()));
}
