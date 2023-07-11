
#include <Socket/Socket.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Socket::Socket(IP ip, Port port)
	: _ip(ip), _port(port), _fd(-1), _domain(AF_INET), _type(SOCK_STREAM), _protocol(0)
{
	/* Create socket */
	this->_fd = socket(this->_domain, this->_type, this->_protocol);
	/* Check for socket errors */

	/* Init sockaddr */
	memset(&this->_sockaddr, 0, sizeof(this->_sockaddr));
	this->_sockaddr.sin_family = this->_domain;
	this->_sockaddr.sin_port = htons(this->_port.getPort());
	this->_sockaddr.sin_addr.s_addr = inet_addr(this->_ip.getAddress().c_str());
}

// Socket::Socket(IP ip, Port port, int domain, int type, int protocol)
// 	: _ip(ip), _port(port), _fd(-1), _domain(domain), _type(type), _protocol(protocol)
// {
// 	/* Create socket */
// 	this->_fd = socket(this->_domain, this->_type, this->_protocol);
// 	/* Check for socket errors */

// 	/* Init sockaddr */
// 	memset(&this->_sockaddr, 0, sizeof(this->_sockaddr));
// 	this->_sockaddr.sin_family = this->_domain;
// 	this->_sockaddr.sin_port = htons(this->_port.getPort());
// 	this->_sockaddr.sin_addr.s_addr = inet_addr(this->_ip.getAddress().c_str());
// }

Socket::Socket(const Socket &src)
	: _ip(src.getIp()), _port(src.getPort()), _fd(src.getFd()),
	_domain(src.getDomain()), _type(src.getType()), _protocol(src.getProtocol())
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Socket::~Socket()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Socket &Socket::operator=(Socket const &rhs)
{
	if (this != &rhs)
	{
		this->_fd = rhs.getFd();
		this->_domain = rhs.getDomain();
		this->_type = rhs.getType();
		this->_protocol = rhs.getProtocol();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, Socket const &i)
{
	o << "Socket[" << i.getFd() << "]";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void Socket::bind(void)
{
	::bind(this->_fd, reinterpret_cast<const sockaddr *>(&this->_sockaddr), sizeof(this->_sockaddr));
}

void Socket::listen(void)
{
	::listen(this->_fd, MAX_SYS_BACKLOG);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

IP Socket::getIp(void) const
{
	return this->_ip;
}

Port Socket::getPort(void) const
{
	return this->_port;
}

int Socket::getFd(void) const
{
	return this->_fd;
}

int Socket::getDomain(void) const
{
	return this->_domain;
}

int Socket::getType(void) const
{
	return this->_type;
}

int Socket::getProtocol(void) const
{
	return this->_protocol;
}

/* ************************************************************************** */
