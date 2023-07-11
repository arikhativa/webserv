
#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <sys/poll.h>
#include <unistd.h>
#include <fcntl.h>
#include "Socket/Socket.hpp"

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
	Server();
	~Server();

	void start();
	void bindSockets();
	void listenSockets();

  private:
	// A config file var
	Socket **_listener;
	unsigned int _listenerSize;
	enum status _status;

	struct pollfd *_poll;
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* SERVER_HPP */
