
#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "ServerConf/ServerConf.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

#include "../IP/IP.hpp"
#include "../Port/Port.hpp"

#ifdef TEST_ON
#define private public
#define protected public
#endif

#ifndef SO_NOSIGPIPE
#define SO_NOSIGPIPE 0
#endif

#define MAX_SYS_BACKLOG 128

class Socket
{
  public:
	explicit Socket(const IListen *);
	Socket(Socket const &src);
	~Socket();

	const IListen *getListen(void) const;
	IP getIp(void) const;
	Port getPort(void) const;
	int getFd(void) const;
	int getDomain(void) const;
	int getType(void) const;
	int getProtocol(void) const;

	void bind();
	void listen();
	void close();

	class SocketCreationFailed : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};
	class SocketListeningFailed : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};
	class SocketBindingFailed : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};
	class SocketNotBinded : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

	bool operator==(const Socket &src);

  private:
	const IListen *_listen;
	const IP _ip;
	const Port _port;
	bool _binded;
	int _fd;
	int _domain;
	int _type;
	int _protocol;
	struct sockaddr_in _sockaddr;

	void _setFd(int value);
};

std::ostream &operator<<(std::ostream &o, Socket const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* SOCKET_HPP */
