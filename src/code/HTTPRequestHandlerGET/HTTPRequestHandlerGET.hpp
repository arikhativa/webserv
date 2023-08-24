#ifndef HTTPREQUESTHANDLERGET_HPP
#define HTTPREQUESTHANDLERGET_HPP

#include <fstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <BasicHTTPRequest/BasicHTTPRequest.hpp>
#include <CgiManager/CgiManager.hpp>
#include <FileManager/FileManager.hpp>
#include <HTTPRequestHandler/HTTPRequestHandler.hpp>
#include <ResponseHeader/ResponseHeader.hpp>
#include <Server/Server.hpp>

namespace httprequesthandlerGET
{
	bool isFileExists(const std::string &path);
	bool isDirectory(const std::string &path);
	bool isChunked(const std::string &request);
	std::string getUnchunkedBody(const std::string &bodyRequest);
	std::string getQueryCGIArgs(const std::string &request);
	std::string getCGI(const std::string &path, Server server, BasicHTTPRequest request, ResponseHeader &response);
	std::string getFileContent(const std::string &path, Server server, BasicHTTPRequest request,
							   ResponseHeader &response);
	std::string getDirecoryContent(const std::string &path, const std::string &name);
	std::string createpipe(char **ch_env, char **argv, const std::string &bodyRequest);
	char **setEnv(std::string bodyRequest, const std::string &path, std::string request, Server server);
	void free_argv_env(char **ch_env, char **argv);

	class cgiGETException : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};
} // namespace httprequesthandlerGET

#endif