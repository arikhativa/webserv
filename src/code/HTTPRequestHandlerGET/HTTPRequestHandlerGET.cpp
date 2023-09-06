#include <HTTPRequestHandlerGET/HTTPRequestHandlerGET.hpp>

bool httprequesthandlerGET::isDirectoryListing(const Path &path, const HTTPCall &request)
{
	return (FileManager::isDirectory(path.get()) && request.isAutoIndexOn());
}

std::string httprequesthandlerGET::getFileContent(const std::string &path, ResponseHeader &response)
{
	if (path.find(".") != std::string::npos)
		response.setContentType(path.substr(path.find_last_of(".")));
	return (FileManager::getFileContent(path));
}

std::string httprequesthandlerGET::getDirecoryContent(const Path &path, const Path &name)
{
	return (FileManager::getDirectoryPreview(path.get(), name.get()));
}
