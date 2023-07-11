
#include <Server/Server.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Server::Server()
	:_listenerSize(2), _status(STOPED)
{
	this->_listener = new Socket*[this->_listenerSize];
	this->_poll = new struct pollfd[this->_listenerSize];

	memset(this->_listener, 0, this->_listenerSize);
	memset(this->_poll, 0, this->_listenerSize);

	/* Create listeners according to the config file */
	for (size_t i = 0; i < this->_listenerSize; i++)
	{
		if (i == 0)
			this->_listener[i] = new Socket(IP("127.0.0.1"), Port(1234));
		else if (i == 1)
			this->_listener[i] = new Socket(IP("127.0.0.1"), Port(4321));
		// fcntl(this->_listener[i]->getFd(), F_SETFL, O_NONBLOCK);
		this->_poll[i].fd = this->_listener[i]->getFd();
		this->_poll[i].events = POLLIN;
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

void Server::start(void)
{
	int pollCnt;
	int tmp_client;

	this->_status = RUNNING;
	while (RUNNING == this->_status)
	{
		/* TODO: Must be non-blocking (?) */
		pollCnt = poll(this->_poll, this->_listenerSize, -1);
		(void)pollCnt;
		for (unsigned int i = 0; i < this->_listenerSize; i++)
		{
			if (!this->_poll[i].revents)
				continue ;
			/* Handle Client Request */
			{
				/*
				 * Nginx does not close connection after the client send the request,
				 * tmp_client could be stored in a client-fd array and delete it server shutdown
				 * TODO: IT DOES CLOSE THE CONNECTION BUT AFTER 5 LINE BREAKS ~weird~
				*/
				tmp_client = accept(this->_listener[i]->getFd(), NULL, NULL);
				if (tmp_client <= -1)
					continue ;
				HTTPRequest http(tmp_client);
				http.recvRequest();
				http.handleRequest();
				http.sendResponse();
				close(tmp_client);
			}
		}
	}
}

void Server::bindSockets()
{
	for (size_t i = 0; i < this->_listenerSize; i++)
		this->_listener[i]->bind();
}

void Server::listenSockets()
{
	for (size_t i = 0; i < this->_listenerSize; i++)
		this->_listener[i]->listen();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */
