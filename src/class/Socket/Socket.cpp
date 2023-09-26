
#include <Socket/Socket.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Socket::Socket(const IListen *listen)
	: _listen(listen)
	, _ip(listen->getAddress().get())
	, _port(listen->getPort().get())
	, _binded(false)
	, _fd(-1)
	, _domain(AF_INET)
	, _type(SOCK_STREAM)
	, _protocol(0)
{
	/* Create socket */
	this->_fd = socket(this->_domain, this->_type, this->_protocol);
	if (this->_fd <= -1)
		throw SocketCreationFailed();

	/* Set the socket to reuse (makes it re-bindable directly after close) */
	int reuse_addr = true;
	setsockopt(this->_fd, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(reuse_addr));

	/* Init sockaddr */
	memset(&this->_sockaddr, 0, sizeof(this->_sockaddr));
	this->_sockaddr.sin_family = this->_domain;
	this->_sockaddr.sin_port = htons(this->_port.get());
	this->_sockaddr.sin_addr.s_addr = inet_addr(this->_ip.get().c_str());
}

Socket::Socket(Socket const &src)
	: _listen(src._listen)
	, _ip(src._ip)
	, _port(src._port)
	, _binded(src._binded)
	, _fd(src._fd)
	, _domain(src._domain)
	, _type(src._type)
	, _protocol(src._protocol)
	, _sockaddr(src._sockaddr)
{
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
const char *Socket::SocketNotBinded::what() const throw()
{
	return "Socket not binded";
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

std::ostream &operator<<(std::ostream &o, Socket const &i)
{
	o << i.getIp() << ":" << i.getPort().get() << ":[" << i.getFd() << "]";
	return o;
}

bool Socket::operator==(const Socket &src)
{
	if (this->_ip.get() == src._ip.get() && this->_port.get() == src._port.get())
		return true;
	return false;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void Socket::bind(void)
{
	int bind_status;
	if (this->_binded)
		return;
	bind_status = ::bind(this->_fd, reinterpret_cast< const sockaddr * >(&this->_sockaddr), sizeof(this->_sockaddr));
	if (bind_status <= -1)
		throw SocketBindingFailed();
	this->_binded = true;
}

void Socket::listen(void)
{
	int listen_status;
	if (!this->_binded)
		throw SocketNotBinded();
	listen_status = ::listen(this->_fd, MAX_SYS_BACKLOG);
	if (listen_status <= -1)
		throw SocketListeningFailed();
}

void Socket::close(void)
{
	if (this->_fd >= -1)
		::close(this->_fd);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

const IListen *Socket::getListen(void) const
{
	return this->_listen;
}

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
