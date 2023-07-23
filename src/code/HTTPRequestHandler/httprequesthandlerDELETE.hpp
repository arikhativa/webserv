#ifndef HTTPREQUESTHANDLERDELETE_HPP
#define HTTPREQUESTHANDLERDELETE_HPP

#include <iostream>
#include <sys/stat.h>
#include <cstdio>

namespace httprequesthandlerDELETE
{
	bool		exists_file(const std::string& path);
}

#endif