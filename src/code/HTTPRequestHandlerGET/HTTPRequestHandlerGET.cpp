#include <HTTPRequestHandlerGET/HTTPRequestHandlerGET.hpp>

bool httprequesthandlerGET::isFileExists(const std::string &path)
{
	return (FileManager::isFileExists(path));
}

bool httprequesthandlerGET::isDirectory(const std::string &path)
{
	return (FileManager::isDirectory(path));
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

const char *httprequesthandlerGET::cgiGETException::what() const throw()
{
	return "Error In cgi";
}
