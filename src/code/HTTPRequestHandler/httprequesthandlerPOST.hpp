#ifndef HTTPREQUESTHANDLERPOST_HPP
#define HTTPREQUESTHANDLERPOST_HPP

#include <iostream>
#include <map>
#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include <sys/wait.h>

#include <Server/Server.hpp>

namespace httprequesthandlerPOST
{
	std::string	getBody(std::string request);
	std::string	getNameFilePost(std::string body);
	std::string	getContentFilePost(std::string body);
	bool		exists_file(const std::string& path);
	bool		is_directory(const std::string& path);
	std::map<std::string, std::string>	getParameters(std::string query);
	std::string getQuery(std::string request);
	std::string getQueryCGIArgs(std::string request);
	std::string getFileContent(const std::string& path, Server server, std::string request);
	std::string getCGI(const std::string& path, Server server, std::string request);
	std::string createpipe(char **ch_env, char **argv, std::string bodyRequest);
	char **		setEnv(std::string bodyRequest, const std::string& path, std::string request, Server server);
	std::string	getUnchunkedBody(std::string bodyRequest);
	bool		isChunked(std::string request);
}

#endif