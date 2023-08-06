#ifndef HTTPREQUESTHANDLERDELETE_HPP
#define HTTPREQUESTHANDLERDELETE_HPP

#include <FileManager/FileManager.hpp>

#include <cstdio>
#include <iostream>

namespace httprequesthandlerDELETE
{
	bool isFileExists(const std::string &path);
	bool isDirectory(const std::string &path);
	void deleteFile(const std::string &path);
	class DeleteFileException : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};
} // namespace httprequesthandlerDELETE

#endif