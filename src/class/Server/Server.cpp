
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
		/* Must be non-blockin (?) */
		pollCnt = poll(this->_poll, this->_listenerSize, -1);
		(void)pollCnt;
		for (unsigned int i = 0; i < this->_listenerSize; i++)
		{
			if (!this->_poll[i].revents)
				continue ;
			tmp_client = accept(this->_listener[i]->getFd(), NULL, NULL);
			/* Handle Client Request*/
				char buff[512];
				read(tmp_client, buff, sizeof(buff));
				write(tmp_client, buff, strlen(buff));

				write(1, buff, strlen(buff));
				memset(buff, 0, sizeof(buff));
				close(tmp_client);
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
