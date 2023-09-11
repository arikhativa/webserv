#ifndef HTTPREQUESTHANDLERDELETE_HPP
#define HTTPREQUESTHANDLERDELETE_HPP

#include <FileManager/FileManager.hpp>
#include <Path/Path.hpp>

#include <cstdio>
#include <iostream>

namespace httprequesthandlerDELETE
{
	void deleteFile(const Path &path);
	class DeleteFileException : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};
} // namespace httprequesthandlerDELETE

#endif