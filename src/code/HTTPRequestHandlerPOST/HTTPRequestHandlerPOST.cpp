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

std::string httprequesthandlerPOST::getFileContent(const std::string &path, ResponseHeader &response)
{
	std::string content = FileManager::getFileContent(path);
	if (path.find(".") != std::string::npos)
		response.setContentType(path.substr(path.find_last_of(".")));
	return (content);
}
