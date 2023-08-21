
#include <Server/Server.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

// TODO: this method is using for testing, should be removed later
Server::Server(int port0, int port1)
{
	this->_listener.push_back(Socket(IP("127.0.0.1"), Port(port0)));
	this->_listener.push_back(Socket(IP("127.0.0.1"), Port(port1)));
}

// Server::Server(serverName, rootPath, listen, errorPage, return, clientMaxBody, location);
// {

// }

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
	std::vector<Socket>::iterator it = this->_listener.begin();
	std::vector<Socket>::iterator end = this->_listener.end();
	for (; it != end; it++)
		it->close();
}

void Server::bindSockets()
{
	std::vector<Socket>::iterator it = this->_listener.begin();
	std::vector<Socket>::iterator end = this->_listener.end();
	for (; it != end; it++)
		it->bind();
}

void Server::listenSockets()
{
	std::vector<Socket>::iterator it = this->_listener.begin();
	std::vector<Socket>::iterator end = this->_listener.end();
	for (; it != end; it++)
		it->listen();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

const std::vector<int> Server::getListeners(void) const
{
	std::vector<int> fds;

	std::vector<Socket>::const_iterator it = this->_listener.begin();
	std::vector<Socket>::const_iterator end = this->_listener.end();
	for (; it != end; it++)
		fds.push_back(it->getFd());
	return fds;
}

int Server::getListenersSize(void) const
{
	return this->_listener.size();
}

/* ************************************************************************** */
