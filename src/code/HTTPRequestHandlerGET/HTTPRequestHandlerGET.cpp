#include <HTTPRequestHandlerGET/HTTPRequestHandlerGET.hpp>

bool httprequesthandlerGET::isDirectoryListing(const Path &path, const HTTPCall &request)
{
	return (FileManager::isDirectory(path.get()) && matcher::isAutoIndexOnToRequest(request));
}

std::string httprequesthandlerGET::getFileContent(const std::string &path, ResponseHeader &response, HTTPCall &request)
{
	if (matcher::isCgiToRequest(request))
	{
		Path pathCGI("/usr/bin/python3");
		std::string serverName = "";
		//! TODO revisar
		if (request.getSocket() == NULL)
			throw std::runtime_error("Error: socket is null");
		Port port = request.getSocket()->getPort();

		CgiManager cgi_obj(request.getBasicRequest(), pathCGI, serverName, port.get() + "");
		return (cgi_obj.executeCgiManager(matcher::rootToRequest(request)));
	}
	if (path.find(".") != std::string::npos)
		response.setContentType(path.substr(path.find_last_of(".")));
	return (FileManager::getFileContent(path));
}

std::string httprequesthandlerGET::getDirecoryContent(const Path &path, const Path &name)
{
	return (FileManager::getDirectoryPreview(path.get(), name.get()));
}
