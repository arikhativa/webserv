#include <httpRequestHandlerDELETE/httpRequestHandlerDELETE.hpp>

void httprequesthandlerDELETE::deleteFile(const Path &path)
{
	if (remove(path.get().c_str()) != 0)
		throw httprequesthandlerDELETE::DeleteFileException();
}

const char *httprequesthandlerDELETE::DeleteFileException::what() const throw()
{
	return ("Failed to delete file");
}