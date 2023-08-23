
#include <ServerManager/ServerManager.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ServerManager::ServerManager(const IConf *conf)
	: _conf(conf)
	, _status(STOPED)
{
	// this->_virtualServers.push_back(Server(1234, 4321));
	// this->_virtualServers.push_back(Server(1235, 5321));
	// this->_virtualServers.push_back(Server(1236, 6321));

	std::list<const IServerConf *> servers = conf->getServers();
	std::list<const IServerConf *>::iterator it = servers.begin();
	std::list<const IServerConf *>::iterator end = servers.end();
	for (; it != end; it++)
	{
		this->_virtualServers.push_back(Server(*it));
	}

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

void ServerManager::close(void)
{
	/* Terminate all pending requests */
	std::vector<HTTPRequest *>::iterator it_http = this->_pendingRequests.begin();
	std::vector<HTTPRequest *>::iterator end_http = this->_pendingRequests.end();
	for (; it_http != end_http; it_http++)
	{
		(*it_http)->terminate();
		this->_pendingRequests.erase(it_http);
	}
	/* Close all servers*/
	std::vector<Server>::iterator it_server = this->_virtualServers.begin();
	std::vector<Server>::iterator end_server = this->_virtualServers.end();
	for (; it_server != end_server; it_server++)
		it_server->closeSockets();
}

void ServerManager::setup()
{
	std::vector<Server>::iterator it = this->_virtualServers.begin();
	std::vector<Server>::iterator end = this->_virtualServers.end();
	for (int i = 0; it != end; it++)
	{
		it->bindSockets();
		it->listenSockets();
		std::vector<int> fds = it->getSockets();
		std::vector<int>::iterator it_fds = fds.begin();
		std::vector<int>::iterator end_fds = fds.end();
		for (; it_fds != end_fds; i++, it_fds++)
		{
			this->_poll[i].fd = *it_fds;
			this->_poll[i].events = POLLIN;
			this->_pollServer.insert(std::pair<struct pollfd *, Server *>(this->_poll + i, &(*it)));
		}
	}
}
#include <errno.h>
#include <stdio.h>
void ServerManager::start()
{
	int pollCnt;
	int tmp_client;
	int timeOut = -1;

	this->_status = RUNNING;
	std::cout << "Starting server..." << std::endl;
	while (RUNNING == this->_status)
	{
		/* TODO: Must be non-blocking (?) */
		pollCnt = poll(this->_poll, this->_pollSize, timeOut);
		(void)pollCnt;
		for (int i = 0; i < this->_pollSize; i++)
		{
			if (!this->_poll[i].revents)
				continue;
			/* Handle Client Request */
			tmp_client = Server::acceptConnection(this->_poll[i].fd);
			if (tmp_client <= -1)
				continue;
			this->_pendingRequests.push_back(new HTTPRequest(*this->_pollServer.at(this->_poll + i), tmp_client));
		}
		std::vector<HTTPRequest *>::iterator it = this->_pendingRequests.begin();
		std::vector<HTTPRequest *>::iterator end = this->_pendingRequests.end();
		for (; it != end; it++)
		{
			try
			{
				(*it)->recvRequest();
				(*it)->handleRequest();
				(*it)->sendResponse();
				(*it)->terminate();
				this->_pendingRequests.erase(it);
			}
			catch (const std::exception &e)
			{
				if ((*it)->getAttempts() >= HTTPRequest::MAX_REQUEST_ATTEMPTS)
				{
					(*it)->terminate();
					this->_pendingRequests.erase(it);
				}
			}
		}
		if (this->_pendingRequests.empty())
			timeOut = -1;
		else
			timeOut = 200;
		std::cout << "Pending requests: " << this->_pendingRequests.size() << std::endl;
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
		pollSize += it->getSocketListSize();
	return pollSize;
}

/* ************************************************************************** */
