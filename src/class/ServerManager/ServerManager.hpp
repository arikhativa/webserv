
#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <Server/Server.hpp>
#include <sys/poll.h>
#include <HTTPRequest/HTTPRequest.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class ServerManager
{
  public:
	ServerManager();
	// explicit ServerManager(Config config);
	~ServerManager();

  private:
	enum status _status;
	unsigned int _listenerSize;
	std::vector<Server> _virtualServers;

	struct pollfd *_poll;
	std::map<struct pollfd *, Server> _pollServer;
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* SERVER_MANAGER_HPP */
