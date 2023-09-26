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

class HTTPCall;

namespace httpRequestHandlerPOST
{
	bool isDirectoryListing(const Path &path, const HTTPCall &request);
	bool isFileUpload(const HTTPCall &request);
	std::string getFileContent(const std::string &path, ResponseHeader &response);
	std::string getDirectoryContent(const IPath *path, const Path &name);

	class FORBIDDEN : public std::exception
	{
		virtual const char *what() const throw();
	};
} // namespace httpRequestHandlerPOST

#endif