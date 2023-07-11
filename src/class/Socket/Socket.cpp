
#include <Socket/Socket.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Socket::Socket(IP ip, Port port)
	: _ip(ip)
	, _port(port)
	, _fd(-1)
	, _domain(AF_INET)
	, _type(SOCK_STREAM)
	, _protocol(0)
{
	/* Create socket */
	this->_fd = socket(this->_domain, this->_type, this->_protocol);
	if (this->_fd <= -1)
		throw SocketCreationFailed();

	/* Init sockaddr */
	memset(&this->_sockaddr, 0, sizeof(this->_sockaddr));
	this->_sockaddr.sin_family = this->_domain;
	this->_sockaddr.sin_port = htons(this->_port.get());
	this->_sockaddr.sin_addr.s_addr = inet_addr(this->_ip.getAddress().c_str());
}

const char *Socket::SocketCreationFailed::what() const throw()
{
	return "Socket creation failed";
}
const char *Socket::SocketListeningFailed::what() const throw()
{
	return "Socket setting to listening mode failed";
}
const char *Socket::SocketBindingFailed::what() const throw()
{
	return "Socket binding failed";
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Socket::~Socket()
{
	if (this->_fd >= 0)
		close(this->_fd);
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

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
	int bind_status;
	bind_status = ::bind(this->_fd, reinterpret_cast<const sockaddr *>(&this->_sockaddr), sizeof(this->_sockaddr));
	if (bind_status <= -1)
		throw SocketBindingFailed();
}

void Socket::listen(void)
{
	int listen_status;
	listen_status = ::listen(this->_fd, MAX_SYS_BACKLOG);
	if (listen_status <= -1)
		throw SocketListeningFailed();
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
