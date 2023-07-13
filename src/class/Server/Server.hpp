
#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <sys/poll.h>
#include <unistd.h>
#include <fcntl.h>
#include "Socket/Socket.hpp"
// #include "HTTPRequest/HTTPRequest.hpp"

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
	Server(void);
	//explicit Server(Config config);
	~Server(void);

	// void start();
	void acceptConnections(const struct pollfd *poll);
	void bindSockets(void);
	void listenSockets(void);
	const std::vector<Socket> getListeners(void) const;

  private:
	//Config config;
	std::vector<Socket> _listener;
	unsigned int _listenerSize;
	enum status _status;
	// struct pollfd *_poll;
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* SERVER_HPP */
