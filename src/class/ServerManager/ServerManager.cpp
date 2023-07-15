
#include <ServerManager/ServerManager.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

/* Server should be initialized using the config file, but we dont have it ready yet */
ServerManager::ServerManager()
	:_status(STOPED)
{
	this->_virtualServers.push_back(Server(1234, 4321));
	this->_virtualServers.push_back(Server(1235, 5321));
	this->_virtualServers.push_back(Server(1236, 6321));

	// Set the pollSize after virtualServers setup
	this->_pollSize = this->getTotalListeners();
	this->_poll = new struct pollfd[this->_pollSize];
}

// ServerManager::ServerManager(Config config)
// 	: _value(i)
// {
// }

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ServerManager::~ServerManager()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

/*
** --------------------------------- METHODS ----------------------------------
*/

void ServerManager::setup()
{
	std::vector<Server>::iterator it = this->_virtualServers.begin();
	std::vector<Server>::iterator end = this->_virtualServers.end();
	for (int i = 0; it != end; it++)
	{
		it->bindSockets();
		it->listenSockets();
		std::vector<int> fds = it->getListeners();
		std::vector<int>::iterator it_fds = fds.begin();
		std::vector<int>::iterator end_fds = fds.end();
		for (; it_fds != end_fds; i++, it_fds++)
		{
			this->_poll[i].fd = *it_fds;
			this->_poll[i].events = POLLIN;
			this->_pollServer.insert(std::pair<struct pollfd *, Server*>(this->_poll + i, &(*it)));
		}
	}
}

void ServerManager::start()
{
	int pollCnt;
	int tmp_client;

	this->_status = RUNNING;
	while (RUNNING == this->_status)
	{
		/* TODO: Must be non-blocking (?) */
		std::cout << "Poll is starting" << std::endl;
		pollCnt = poll(this->_poll, this->_pollSize, -1);
		std::cout << "Incoming connections: " << pollCnt << std::endl;
		(void)pollCnt;
		for (int i = 0; i < this->_pollSize; i++)
		{
			if (!this->_poll[i].revents)
				continue ;
			/* Handle Client Request */
			{
				tmp_client = Server::acceptConnection(this->_poll[i].fd);
				if (tmp_client <= -1)
					continue ;
				HTTPRequest http = HTTPRequest(*this->_pollServer.at(this->_poll + i), tmp_client);
				http.recvRequest();
				http.handleRequest();
				http.sendResponse();
				close(tmp_client);
			}
		}
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

int ServerManager::getTotalListeners(void) const
{
	int pollSize = 0;
	std::vector<Server>::const_iterator it = this->_virtualServers.begin();
	std::vector<Server>::const_iterator end = this->_virtualServers.end();
	for (; it != end; it++)
		pollSize += it->getListenersSize();
	return pollSize;
}

/* ************************************************************************** */
