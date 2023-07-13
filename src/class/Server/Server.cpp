
#include <Server/Server.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Server::Server()
	:_listenerSize(1), _status(STOPED)
{
	// this->_poll = new struct pollfd[this->_listenerSize];

	// memset(this->_poll, 0, this->_listenerSize);

	/* Create listeners according to the config file */
	for (size_t i = 0; i < this->_listenerSize; i++)
	{
		this->_listener.push_back(Socket(IP("127.0.0.1"), Port(1234)));
		// fcntl(this->_listener[i]->getFd(), F_SETFL, O_NONBLOCK);
		// this->_poll[i].fd = this->_listener[i]->getFd();
		// this->_poll[i].events = POLLIN;
	}
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

/* This function belongs to server manager */
// void Server::start(void)
// {
// 	int pollCnt;

// 	this->_status = RUNNING;
// 	while (RUNNING == this->_status)
// 	{
// 		/* TODO: Must be non-blocking (?) */
// 		pollCnt = poll(this->_poll, this->_listenerSize, -1);
// 		(void)pollCnt;
// 		this->acceptConnection();
// 		for (unsigned int i = 0; i < this->_listenerSize; i++)
// 		{
// 			if (!this->_poll[i].revents)
// 				continue ;
// 			/* Handle Client Request */
// 			{
// 				/*
// 				 * Nginx does not close connection after the client send the request,
// 				 * tmp_client could be stored in a client-fd array and delete it server shutdown
// 				 * TODO: IT DOES CLOSE THE CONNECTION BUT AFTER 5 LINE BREAKS ~weird~
// 				*/
// 				tmp_client = accept(this->_listener[i]->getFd(), NULL, NULL);
// 				if (tmp_client <= -1)
// 					continue ;
// 				HTTPRequest http(tmp_client);
// 				http.recvRequest();
// 				http.handleRequest();
// 				http.sendResponse();
// 				close(tmp_client);
// 			}
// 		}
// 	}
// }

void Server::acceptConnections(const struct pollfd *poll)
{
	int tmp_client;

	for (unsigned int i = 0; i < this->_listenerSize; i++)
	{
		if (!poll[i].revents)
			continue ;
		/* Handle Client Request */
		{
			/*
				* Nginx does not close connection after the client send the request,
				* tmp_client could be stored in a client-fd array and delete it server shutdown
				* TODO: IT DOES CLOSE THE CONNECTION BUT AFTER 5 LINE BREAKS ~weird~
			*/
			tmp_client = accept(this->_listener.at(i).getFd(), NULL, NULL);
			if (tmp_client <= -1)
				continue ;
			// HTTPRequest http(tmp_client);
			// http.recvRequest();
			// http.handleRequest();
			// http.sendResponse();
			close(tmp_client);
		}
	}
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

const std::vector<Socket> Server::getListeners(void) const
{
	return this->_listener;
}

/* ************************************************************************** */
