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

namespace httprequesthandlerPOST
{
	bool isFileExists(const std::string &path);
	bool isDirectory(const std::string &path);
	std::string getFileContent(const std::string &path, ResponseHeader &response);
} // namespace httprequesthandlerPOST

#endif