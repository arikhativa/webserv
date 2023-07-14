
#include <Server/Server.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Server::Server()
	:_status(STOPED)
{
	this->_listener.push_back(Socket(IP("127.0.0.1"), Port(1234)));
}

Server::Server(int port)
	: _listenerSize(1)
	, _status(STOPED)
{
	// this->_poll = new struct pollfd[this->_listenerSize];

	// memset(this->_poll, 0, this->_listenerSize);

	/* Create listeners according to the config file */
	for (size_t i = 0; i < this->_listenerSize; i++)
	{
		/* Example */
		this->_listener.push_back(Socket(IP("127.0.0.1"), Port(port)));
		// fcntl(this->_listener[i]->getFd(), F_SETFL, O_NONBLOCK);
		// this->_poll[i].fd = this->_listener[i]->getFd();
		// this->_poll[i].events = POLLIN;
	}
}

Server::Server(int port)
	: _listenerSize(1)
	, _status(STOPED)
{
	// this->_poll = new struct pollfd[this->_listenerSize];

	// memset(this->_poll, 0, this->_listenerSize);

	/* Create listeners according to the config file */
	for (size_t i = 0; i < this->_listenerSize; i++)
	{
		/* Example */
		this->_listener.push_back(Socket(IP("127.0.0.1"), Port(port)));
		// fcntl(this->_listener[i]->getFd(), F_SETFL, O_NONBLOCK);
		// this->_poll[i].fd = this->_listener[i]->getFd();
		// this->_poll[i].events = POLLIN;
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
** --------------------------------- METHODS ----------------------------------
*/

HTTPRequest Server::acceptConnection(int socketIndex)
{
	int tmp_client;

	// for (unsigned int i = 0; i < this->_listenerSize; i++)
	// {
	// 	if (!poll[i].revents)
	// 		continue ;
	/* Handle Client Request */
	{
		/*
		 * Nginx does not close connection after the client send the request,
		 * tmp_client could be stored in a client-fd array and delete it server shutdown
		 * TODO: IT DOES CLOSE THE CONNECTION BUT AFTER 5 LINE BREAKS ~weird~
		 */
		tmp_client = accept(this->_listener.at(socketIndex).getFd(), NULL, NULL);
		if (tmp_client <= -1)
			throw Server::AcceptingConnectionFailed();
		return HTTPRequest(tmp_client);
	}
	// }
}

void Server::bindSockets()
{
	for (size_t i = 0; i < this->_listenerSize; i++)
		this->_listener.at(i).bind();
}

void Server::listenSockets()
{
	for (size_t i = 0; i < this->_listenerSize; i++)
		this->_listener.at(i).listen();
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

/* ************************************************************************** */
