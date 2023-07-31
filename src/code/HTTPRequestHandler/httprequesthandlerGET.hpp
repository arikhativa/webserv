#ifndef HTTPREQUESTHANDLERGET_HPP
#define HTTPREQUESTHANDLERGET_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <map>
#include <sys/wait.h>
#include <fstream>
#include <sstream>


#include <Server/Server.hpp>
#include <ILogger/ILogger.hpp>
#include <ResponseHeader/ResponseHeader.hpp>
#include <HTTPRequestHandler/HTTPRequestHandler.hpp>

namespace httprequesthandlerGET
{
	bool		exists_file(const std::string& path);
	bool		is_directory(const std::string& path);
	bool		isChunked(std::string request);
	std::string	getUnchunkedBody(std::string bodyRequest);
	std::string getQueryCGIArgs(std::string request);
	std::string	getCGI(const std::string& path, Server server, std::string request, ResponseHeader &response);
	std::string	getFileContent(const std::string& path, Server server, std::string request, ResponseHeader &response);
	std::string getFileDate(struct stat statbuf);
	std::string getQuery(std::string request);
	std::string treat_url(std::string url);
	std::string	defineUrlDate(std::string path, std::string relative_path, struct dirent *ent, std::string date);
	std::string	getDirecoryContent(const std::string &path,  std::string &name);
	std::map<std::string, std::string>	getParameters(std::string query);
	std::string	createpipe(char **ch_env, char **argv, std::string bodyRequest);
	char 	**	setEnv(std::string bodyRequest, const std::string& path, std::string request, Server server);
	void		free_argv_env(char **ch_env, char **argv);
}

#endif