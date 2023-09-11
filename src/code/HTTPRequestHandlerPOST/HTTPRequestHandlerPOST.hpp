#ifndef HTTPREQUESTHANDLERPOST_HPP
#define HTTPREQUESTHANDLERPOST_HPP

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <sys/stat.h>
#include <sys/wait.h>

#include <BasicHTTPRequest/BasicHTTPRequest.hpp>
#include <FileManager/FileManager.hpp>
#include <HTTPRequestHandler/HTTPRequestHandler.hpp>
#include <ResponseHeader/ResponseHeader.hpp>
#include <Server/Server.hpp>

class HTTPCall;

namespace httprequesthandlerPOST
{
	bool isDirectoryListing(const Path &path, const HTTPCall &request);
	std::string getFileContent(const std::string &path, ResponseHeader &response);
	std::string getDirecoryContent(const Path &path, const Path &name);
} // namespace httprequesthandlerPOST

#endif