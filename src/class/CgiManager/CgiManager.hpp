
#ifndef CGI_MANAGER_HPP
#define CGI_MANAGER_HPP

#include <BasicHTTPRequest/BasicHTTPRequest.hpp>
#include <Path/Path.hpp>
#include <converter/converter.hpp>

#include <cstring>
#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class CgiManager
{
  public:
	explicit CgiManager(const BasicHTTPRequest &basicHTTPRequest, const Path &pathCGI, const std::string &serverName,
						const std::string &port);
	CgiManager(const CgiManager &src);
	~CgiManager();

	CgiManager &operator=(const CgiManager &rhs);

	const Path getPathCGI(void) const;
	const std::string getServerName(void) const;
	const std::string getPort(void) const;
	const BasicHTTPRequest getBasicHTTPRequest(void) const;

	void writeOnInputPipe(const std::string &content);
	const std::string setCgiManager(const Path &pathServer, const std::string &body);

	// exception
	class CgiManagerException : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

  private:
	BasicHTTPRequest _basicHTTPRequest;
	Path _pathCGI;
	std::string _serverName;
	std::string _port;

	int _inputPipe[2];
	int _outputPipe[2];

	std::string _createpipe(char **ch_env, char **argv, const std::string &body);
	char **_setEnv(const std::string &bodyRequest) const;
	void _free_argv_env(char **argv, char **env);

	// void _writeInPipe(int fd, const std::string &str);
};

std::ostream &operator<<(std::ostream &o, const CgiManager &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* CGI_MANAGER_HPP */