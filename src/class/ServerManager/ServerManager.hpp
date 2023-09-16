
#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP

#include <Conf/Conf.hpp>
#include <HTTPCall/HTTPCall.hpp>
#include <IConf/IConf.hpp>
#include <Poll/Poll.hpp>
#include <Server/Server.hpp>
#include <iostream>
#include <map>
#include <matcher/matcher.hpp>
#include <string>
#include <sys/poll.h>
#include <vector>

#ifdef TEST_ON
#define private public
#define protected public
#endif

#define MAX_POLL_SIZE 128

class ServerManager
{
  public:
	enum status
	{
		OK = 0,
		INVALID_VIRTUAL_SERVERS
	};

	ServerManager(const IConf *conf);
	~ServerManager();

	void start();
	void terminate();
	ServerManager::status setup();

  private:
	Poll _poll;
	const IConf *_conf;
	enum status _status;
	std::vector<Server *> _virtual_servers;

	int getTotalListeners(void) const;

  public:
	static Poll::ret_stt clientWrite(Poll &p, int fd, int revents, Poll::Param &param);
	static Poll::ret_stt clientRead(Poll &p, int fd, int revents, Poll::Param &param);
	static Poll::ret_stt initSocketsHandler(Poll &p, int fd, int revents, Poll::Param &param);

	static Poll::ret_stt cgiWrite(Poll &p, int fd, int revents, Poll::Param &param);
	static Poll::ret_stt cgiRead(Poll &p, int fd, int revents, Poll::Param &param);
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* SERVER_MANAGER_HPP */
