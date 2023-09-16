#include <httpRequestHandlerGET/httpRequestHandlerGET.hpp>

bool httpRequestHandlerGET::isDirectoryListing(const Path &path, const HTTPCall &request)
{
	const ILocation *l = request.getLocation();
	if (!l)
	{
		std::cerr << "Error: no location found" << std::endl;
		return (false);
	}

	return (FileManager::isDirectory(path.get()) && request.getLocation()->isAutoIndexOn());
}

std::string httpRequestHandlerGET::getFileContent(const std::string &path, const HTTPCall &request,
												  ResponseHeader &response)
{
	if (request.getLocation()->getCGIConf().isSet() &&
		request.getLocation()->getCGIConf().getExtension() == request.getBasicRequest().getExtension())
	{
		Path pathCGI(request.getLocation()->getCGIConf().getPath());
		Port port = request.getSocket()->getPort();
		const IPath *root(request.getLocation()->getRoot());
		CgiManager cgi_obj(request.getBasicRequest(), pathCGI, request.getServerName(), port.get() + "");
		std::string content = cgi_obj.executeCgiManager(Path(root->get()));
		matcher::cgiToResponse(content, response);
		return (response.getBody());
	}
	response.setContentType(path.substr(path.find_last_of(".")));
	return (FileManager::getFileContent(path));
}

std::string httpRequestHandlerGET::getDirectoryContent(const IPath *path, const Path &name)
{
	return (FileManager::getDirectoryPreview(path->get(), name.get()));
}
