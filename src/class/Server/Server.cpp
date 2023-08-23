
#include <Server/Server.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Server::Server(ServerConf conf)
	: _conf(conf)
{
	std::list<const IListen *> tmpListeners = this->_conf.getListen();
	std::list<const IListen *>::iterator it;
	std::list<const IListen *>::iterator end;
	for (; it != end; it++)
	{
		this->_sockets.push_back(Socket(*it));
	}
}

const char *Server::AcceptingConnectionFailed::what() const throw()
{
	return "Accepting connection failed";
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Server::~Server()
{
}

/*
** ------------------------------ STATIC METHODS -------------------------------
*/

int Server::acceptConnection(int fd)
{
	int tmp_client;

	tmp_client = accept(fd, NULL, NULL);
	if (tmp_client <= -1)
		throw Server::AcceptingConnectionFailed();
	return tmp_client;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void Server::closeSockets(void)
{
	std::vector<Socket>::iterator it = this->_sockets.begin();
	std::vector<Socket>::iterator end = this->_sockets.end();
	for (; it != end; it++)
		it->close();
}

void Server::bindSockets()
{
	std::vector<Socket>::iterator it = this->_sockets.begin();
	std::vector<Socket>::iterator end = this->_sockets.end();
	for (; it != end; it++)
		it->bind();
}

void Server::listenSockets()
{
	std::vector<Socket>::iterator it = this->_sockets.begin();
	std::vector<Socket>::iterator end = this->_sockets.end();
	for (; it != end; it++)
		it->listen();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

const std::vector<int> Server::getSockets(void) const
{
	std::vector<int> fds;

	std::vector<Socket>::const_iterator it = this->_sockets.begin();
	std::vector<Socket>::const_iterator end = this->_sockets.end();
	for (; it != end; it++)
		fds.push_back(it->getFd());
	return fds;
}

int Server::getSocketListSize(void) const
{
	return this->_sockets.size();
}

/* ************************************************************************** */
