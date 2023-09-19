
#include <Server/Server.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Server::Server(const IServerConf *conf)
	: _conf(conf)
{
	std::list<const IListen *> tmpListeners = this->_conf->getListen();
	std::list<const IListen *>::iterator it = tmpListeners.begin();
	std::list<const IListen *>::iterator end = tmpListeners.end();
	for (; it != end; it++)
	{
		this->_sockets.push_back(new Socket(*it));
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
	std::vector<Socket *>::iterator it = this->_sockets.begin();
	std::vector<Socket *>::iterator end = this->_sockets.end();
	for (; it != end; it++)
	{
		(*it)->close();
		delete *it;
	}
}

void Server::bindSockets()
{
	std::vector<Socket *>::iterator it = this->_sockets.begin();
	std::vector<Socket *>::iterator end = this->_sockets.end();
	for (; it != end; it++)
		(*it)->bind();
}

void Server::listenSockets()
{
	std::vector<Socket *>::iterator it = this->_sockets.begin();
	std::vector<Socket *>::iterator end = this->_sockets.end();
	for (; it != end; it++)
		(*it)->listen();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

const std::vector<int> Server::getSocketsFd(void) const
{
	std::vector<int> fds;

	std::vector<Socket *>::const_iterator it = this->_sockets.begin();
	std::vector<Socket *>::const_iterator end = this->_sockets.end();
	for (; it != end; it++)
		fds.push_back((*it)->getFd());
	return fds;
}

const std::vector<Socket *> &Server::getSockets(void) const
{
	return this->_sockets;
}

size_t Server::getSocketListSize(void) const
{
	return this->_sockets.size();
}

const IServerConf *Server::getConf(void) const
{
	return this->_conf;
}

std::list<const IErrorPage *> Server::getErrorPages(void) const
{
	return this->_conf->getErrorPages();
}

std::string Server::getName(void) const
{
	return this->_conf->getNames().front();
}

/* ************************************************************************** */
