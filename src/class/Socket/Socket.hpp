
#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "../IP/IP.hpp"
#include "../Port/Port.hpp"

#ifdef TEST_ON
#define private public
#define protected public
#endif

#define MAX_SYS_BACKLOG 128

class Socket
{
  public:
	explicit Socket(IP ip, Port port);
	Socket(Socket const &src);
	~Socket();

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

  private:
	const IP _ip;
	const Port _port;
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
