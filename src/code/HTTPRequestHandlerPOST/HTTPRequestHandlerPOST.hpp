#ifndef HTTPREQUESTHANDLERPOST_HPP
#define HTTPREQUESTHANDLERPOST_HPP

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <sys/stat.h>
#include <sys/wait.h>

#include <HTTPRequestHandler/HTTPRequestHandler.hpp>
#include <BasicHTTPRequest/BasicHTTPRequest.hpp>
#include <ResponseHeader/ResponseHeader.hpp>
#include <FileManager/FileManager.hpp>
#include <CgiManager/CgiManager.hpp>
#include <Server/Server.hpp>

namespace httprequesthandlerPOST
{
	bool isFileExists(const std::string &path);
	bool isDirectory(const std::string &path);
	std::string getBody(std::string request);
	std::string getContentFilePost(std::string body);
	std::string getQueryCGIArgs(std::string request);
	std::string getFileContent(const std::string &path, Server server, BasicHTTPRequest request, ResponseHeader &response);
	std::string getCGI(const std::string &path, Server server, BasicHTTPRequest request, ResponseHeader &response);
	std::string createpipe(char **ch_env, char **argv, std::string bodyRequest);
	char **setEnv(std::string bodyRequest, const std::string &path, std::string request, Server server);
	std::string getUnchunkedBody(std::string bodyRequest);
	bool isChunked(std::string request);
} // namespace httprequesthandlerPOST

#endif