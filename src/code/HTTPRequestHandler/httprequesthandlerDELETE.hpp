#ifndef HTTPREQUESTHANDLERDELETE_HPP
#define HTTPREQUESTHANDLERDELETE_HPP

#include <iostream>
#include <sys/stat.h>
#include <cstdio>

namespace httprequesthandlerDELETE
{
	bool	fileExists(const std::string& path);
	bool	isDirectory(const std::string& path);
	void	deleteFile(const std::string& path);
	class	deleteException : public std::exception
	{
		public:
			virtual const char* what() const throw();
	};
}

#endif