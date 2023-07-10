
#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../IP/IP.hpp"

#ifdef TEST_ON
#define private public
#define protected public
#endif

class Port
{
	private:
		int _port;
	public:
		Port(int port) { this->_port = port; }
		uint16_t getPort() const { return (this->_port); }
};

#define MAX_SYS_BACKLOG 128

class Socket
{
  public:
	Socket();
	explicit Socket(IP ip, Port port);
	// explicit Socket(IP ip, Port port, int domain, int type, int protocol);
	Socket(Socket const &src);
	~Socket();

	Socket &operator=(Socket const &rhs);

	IP getIp(void) const;
	Port getPort(void) const;
	int getFd(void) const;
	int getDomain(void) const;
	int getType(void) const;
	int getProtocol(void) const;

	void bind();
	void listen();

  private:
	IP _ip;
	Port _port;
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
