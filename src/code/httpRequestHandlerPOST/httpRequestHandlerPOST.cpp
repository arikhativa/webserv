#include <httpRequestHandlerPOST/httpRequestHandlerPOST.hpp>

const char *httpRequestHandlerPOST::FORBIDDEN::what() const throw()
{
	return ("403 Forbidden");
}

bool httpRequestHandlerPOST::isDirectoryListing(const Path &path, const HTTPCall &request)
{
	const ILocation *l = request.getLocation();
	if (!l)
	{
		std::cerr << "Error: no location found" << std::endl;
		return (false);
	}
	return (FileManager::isDirectory(path.get()) && request.getLocation()->isAutoIndexOn());
}

std::vector< char > httpRequestHandlerPOST::getFileContent(const std::string &path, ResponseHeader &response)
{

	if (path.find(".") != std::string::npos)
		response.setContentType(path.substr(path.find_last_of(".")));
	return FileManager::getFileContent(path);
}

std::string httpRequestHandlerPOST::getDirectoryContent(const IPath *path, const Path &name)
{
	return (FileManager::getDirectoryPreview(path->get(), name.get()));
}
