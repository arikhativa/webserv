
#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP

#include <Conf/Conf.hpp>
#include <HTTPRequest/HTTPRequest.hpp>
#include <IConf/IConf.hpp>
#include <Poll/Poll.hpp>
#include <Server/Server.hpp>
#include <iostream>
#include <map>
#include <string>
#include <sys/poll.h>
#include <vector>

#ifdef TEST_ON
#define private public
#define protected public
#endif

#define MAX_POLL_SIZE 128

enum status
{
	STOPED = 0,
	RUNNING = 1
};

class ServerManager
{
  public:
	ServerManager(const IConf *conf);
	~ServerManager();

	void start();
	void close();
	void setup();

  private:
	Poll _poll;
	const IConf *_conf;
	enum status _status;
	std::vector<Server> _virtualServers;

	int getTotalListeners(void) const;
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* SERVER_MANAGER_HPP */
