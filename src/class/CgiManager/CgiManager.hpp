
#ifndef CGI_MANAGER_HPP
#define CGI_MANAGER_HPP

#include <BasicHTTPRequest/BasicHTTPRequest.hpp>
#include <Path/Path.hpp>
#include <Pipe/Pipe.hpp>
#include <Tab/Tab.hpp>
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
	~CgiManager();

	Path getPathCGI(void) const;
	const std::string getServerName(void) const;
	const std::string getPort(void) const;
	BasicHTTPRequest getBasicHTTPRequest(void) const;
	void writeToPipe(const std::string &str) const;

	const std::string executeCgiManager(const Path &pathServer);
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
	Tab _env;
	Tab _argv;
	Pipe _pipe;

	void _setEnv(void);
	void _setArgv(const Path &pathServer);
	static int _createFork(void);
	void _childProcess(void);
	std::string _parentProcess(int pid);
	std::string _readCgiOutput(int pid);

	static const int ERROR;
	static const int CHILD;
	static const int BUFFER_SIZE;
};

std::ostream &operator<<(std::ostream &o, const CgiManager &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* CGI_MANAGER_HPP */
