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

#include <fstream>
#include <sstream>


#include <ILogger/ILogger.hpp>

namespace httprequesthandlerGET
{
	bool		exists_file(const std::string& path);
	bool		is_directory(const std::string& path);
	std::string	getFileContent(const std::string& path);
	std::string getFileDate(struct stat statbuf);
	std::string getQuery(std::string request);
	std::string treat_url(std::string url);
	std::string	defineUrlDate(std::string path, std::string relative_path, struct dirent *ent, std::string date);
	std::string	getDirecoryContent(const std::string &path,  std::string &name);
	std::map<std::string, std::string>	getParameters(std::string query);
}

#endif