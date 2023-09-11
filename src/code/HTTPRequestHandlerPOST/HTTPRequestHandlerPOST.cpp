#include <HTTPRequestHandlerPOST/HTTPRequestHandlerPOST.hpp>

bool httprequesthandlerPOST::isDirectoryListing(const Path &path, const HTTPCall &request)
{
	return (FileManager::isDirectory(path.get()) && matcher::isAutoIndexOnToRequest(request));
}

std::string httprequesthandlerPOST::getFileContent(const std::string &path, ResponseHeader &response)
{
	if (path.find(".") != std::string::npos)
		response.setContentType(path.substr(path.find_last_of(".")));
	return (FileManager::getFileContent(path));
}

std::string httprequesthandlerPOST::getDirecoryContent(const Path &path, const Path &name)
{
	return (FileManager::getDirectoryPreview(path.get(), name.get()));
}
