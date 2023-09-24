
#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP

#include <Conf/Conf.hpp>
#include <HTTPCall/HTTPCall.hpp>
#include <IConf/IConf.hpp>
#include <Poll/Poll.hpp>
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

	class ServerCreationFailed : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

	class AcceptingConnectionFailed : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

	void start();
	void terminate();
	void setup();

  private:
	Poll _poll;
	const IConf *_conf;
	enum status _status;
	std::vector< Socket > _sockets;

	void createServerSockets(const IConf *conf);
	static int acceptConnection(int fd);

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
