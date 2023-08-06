#include <HTTPRequestHandlerDELETE/HTTPRequestHandlerDELETE.hpp>

bool httprequesthandlerDELETE::isFileExists(const std::string &path)
{
	return (FileManager::isFileExists(path));
}

bool httprequesthandlerDELETE::isDirectory(const std::string &path)
{
	return (FileManager::isDirectory(path));
}

void httprequesthandlerDELETE::deleteFile(const std::string &path)
{
	if (remove(path.c_str()) != 0)
		throw httprequesthandlerDELETE::DeleteFileException();
}

const char *httprequesthandlerDELETE::DeleteFileException::what() const throw()
{
	return ("Failed to delete file");
}