#include <httpRequestHandlerGET/httpRequestHandlerGET.hpp>

bool httpRequestHandlerGET::isDirectoryListing(const IPath *root, const Path &url, const HTTPCall &request)
{
	const ILocation *l = request.getLocation();
	if (!l)
	{
		std::cerr << "Error: no location found" << std::endl;
		return (false);
	}

	return (request.getLocation()->isAutoIndexOn() && FileManager::isDirectory(root->get() + url.get()));
}

std::string httpRequestHandlerGET::getFileContent(const std::string &path, ResponseHeader &response)
{
	if (path.find(".") != std::string::npos)
		response.setContentType(path.substr(path.find_last_of(".")));
	return (FileManager::getFileContent(path));
}

std::string httpRequestHandlerGET::getDirectoryContent(const IPath *path, const Path &name)
{
	return (FileManager::getDirectoryPreview(path->get(), name.get()));
}
