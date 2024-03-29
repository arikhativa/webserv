
#ifndef HTTPREQUESTHANDLERGET_HPP
#define HTTPREQUESTHANDLERGET_HPP

#include <fstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <BasicHTTPRequest/BasicHTTPRequest.hpp>
#include <CgiManager/CgiManager.hpp>
#include <FileManager/FileManager.hpp>
#include <HTTPCall/HTTPCall.hpp>
#include <HTTPRequestHandler/HTTPRequestHandler.hpp>
#include <ResponseHeader/ResponseHeader.hpp>
#include <matcher/matcher.hpp>

class HTTPCall;

namespace httpRequestHandlerGET
{
	bool isDirectoryListing(const IPath *root, const Path &url, const HTTPCall &request);
	std::vector< char > getFileContent(const std::string &path, ResponseHeader &response);
	std::string getDirectoryContent(const IPath *path, const Path &name);
} // namespace httpRequestHandlerGET

#endif
