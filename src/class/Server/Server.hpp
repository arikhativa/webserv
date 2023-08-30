
#ifndef SERVER_HPP
#define SERVER_HPP

#include "ServerConf/ServerConf.hpp"
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

class Server
{
  public:
	explicit Server(const IServerConf *conf);
	~Server(void);

	class AcceptingConnectionFailed : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

	void bindSockets(void);
	void listenSockets(void);
	const std::vector<int> getSockets(void) const;
	size_t getSocketListSize(void) const;
	void closeSockets(void);

	static int acceptConnection(int socketIndex);

	const IServerConf *getConf(void) const;

  private:
	std::vector<Socket> _sockets;
	const IServerConf *_conf;
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* SERVER_HPP */