#ifndef HTTPREQUESTHANDLERPOST_HPP
#define HTTPREQUESTHANDLERPOST_HPP

#include <iostream>
#include <map>
#include <sys/stat.h>

namespace httprequesthandlerPOST
{
	std::string	getBody(std::string request);
	std::string	getNameFilePost(std::string body);
	std::string	getContentFilePost(std::string body);
	bool		exists_file(const std::string& path);
	std::map<std::string, std::string>	getParameters(std::string query);
	std::string getQuery(std::string request);
}

#endif