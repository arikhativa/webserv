#include <HTTPRequestHandler/httprequesthandlerDELETE.hpp>

bool httprequesthandlerDELETE::fileExists(const std::string &path)
{
	struct stat statbuf;
	return (stat(path.c_str(), &statbuf) == 0);
}

bool httprequesthandlerDELETE::isDirectory(const std::string &path)
{
	struct stat statbuf;
	stat(path.c_str(), &statbuf);
	return (S_ISDIR(statbuf.st_mode));
}

void httprequesthandlerDELETE::deleteFile(const std::string &path)
{
	if (remove(path.c_str()) != 0)
		throw httprequesthandlerDELETE::deleteException();
}

const char *httprequesthandlerDELETE::deleteException::what() const throw()
{
	return ("Failed to delete file");
}