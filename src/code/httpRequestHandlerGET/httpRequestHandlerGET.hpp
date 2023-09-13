
#ifndef HTTPREQUESTHANDLERGET_HPP
#define HTTPREQUESTHANDLERGET_HPP

#include <fstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <BasicHTTPRequest/BasicHTTPRequest.hpp>
#include <FileManager/FileManager.hpp>
#include <HTTPCall/HTTPCall.hpp>
#include <HTTPRequestHandler/HTTPRequestHandler.hpp>
#include <ResponseHeader/ResponseHeader.hpp>
#include <Server/Server.hpp>

class HTTPCall;

namespace httpRequestHandlerGET
{
	bool isDirectoryListing(const Path &path, const HTTPCall &request);
	std::string getFileContent(const std::string &path, ResponseHeader &response);
	std::string getDirectoryContent(const IPath *path, const Path &name);
} // namespace httpRequestHandlerGET

#endif
