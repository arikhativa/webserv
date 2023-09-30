
#ifndef CGI_MANAGER_HPP
#define CGI_MANAGER_HPP

#include <BasicHTTPRequest/BasicHTTPRequest.hpp>
#include <Path/Path.hpp>
#include <Pipe/Pipe.hpp>
#include <Tab/Tab.hpp>
#include <converter/converter.hpp>
#include <header/header.hpp>
#include <vectorUtils/vectorUtils.hpp>

#include <cstring>
#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class CgiManager
{
  public:
	explicit CgiManager(const BasicHTTPRequest &basicHTTPRequest, const Path &pathCGI, const Path &local_path,
						const std::string &serverName, const std::string &port);
	~CgiManager();

	Path getPathCGI(void) const;
	const Pipe &getPipe(void) const;
	const std::string getServerName(void) const;
	const std::string getPort(void) const;
	BasicHTTPRequest getBasicHTTPRequest(void) const;

	int getWriteFd(void) const;
	int getReadFd(void) const;
	int getPid(void) const;
	int getBytesWrite(void) const;
	int getBytesRead(void) const;
	const std::vector< char > &getOutput(void) const;

	void writeToCgi(void);
	void readFromCgi(void);
	void closePipe(void);
	void writeToPipe(const std::string &str) const;

	void executeCgiManager(void);
	class CgiManagerException : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

	class CgiManagerIncompleteRead : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

	class CgiManagerIncompleteWrite : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

  private:
	BasicHTTPRequest _basicHTTPRequest;
	Path _pathCGI;
	const Path &_local_path;
	std::string _serverName;
	std::string _port;
	Tab _env;
	Tab _argv;
	Pipe _pipe;
	std::vector< char > _output;
	int _pid;

	size_t _byte_write;
	size_t _byte_read;

	void _setEnv(void);
	void _setArgv(void);
	static int _createFork(void);
	void _childProcess(void);

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
