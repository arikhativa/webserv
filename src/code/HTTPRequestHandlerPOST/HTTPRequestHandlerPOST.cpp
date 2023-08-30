#include <HTTPRequestHandlerPOST/HTTPRequestHandlerPOST.hpp>

bool httprequesthandlerPOST::isFileExists(const std::string &path)
{
	return (FileManager::isFileExists(path));
}

bool httprequesthandlerPOST::isDirectory(const std::string &path)
{
	return (FileManager::isDirectory(path));
}

std::string httprequesthandlerPOST::getFileContent(const std::string &path, ResponseHeader &response)
{
	std::string content = FileManager::getFileContent(path);
	if (path.find(".") != std::string::npos)
		response.setContentType(path.substr(path.find_last_of(".")));
	return (content);
}
