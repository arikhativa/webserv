#include <HTTPRequestHandler/httprequesthandlerDELETE.hpp>

bool	httprequesthandlerDELETE::exists_file(const std::string& path)
{
	struct stat statbuf;
	return (stat(path.c_str(), &statbuf) == 0);
}