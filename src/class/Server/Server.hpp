
#ifndef SERVER_HPP
#define SERVER_HPP

#include "Socket/Socket.hpp"
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <sys/poll.h>
#include <unistd.h>
#include <vector>

#ifdef TEST_ON
#define private public
#define protected public
#endif

enum status
{
	STOPED = 0,
	RUNNING = 1
};

class Server
{
  public:
	// TODO: this method is using for testing, should be removed later
	explicit Server(int port0, int port1);
	// explicit Server(serverName, rootPath, listen, errorPage, return, clientMaxBody, location);
	~Server(void);

	class AcceptingConnectionFailed : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

	void bindSockets(void);
	void listenSockets(void);
	const std::vector<int> getListeners(void) const;
	int getListenersSize(void) const;
	
	static int acceptConnection(int socketIndex);

  private:
	std::vector<Socket> _listener;
	// _serverName;
	// _rootPath;
	// _listen;
	// _errorPage
	// _return;
	// _cientMaxBody;
	// _location 
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* SERVER_HPP */
