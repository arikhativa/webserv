
#include <ServerManager/ServerManager.hpp>

/* TEST HANDLERS */

Poll::ret_stt client_write(Poll &p, int fd, int revents, Poll::Param &param)
{
	(void)p;
	(void)fd;
	(void)revents;
	(void)param;
	std::cout << "Client Write" << std::endl;
	param.req.sendResponse();
	if (param.req.getBytesSent() < param.req.getResponse().size() ||
		param.req.getResponseAttempts() >= HTTPRequest::MAX_ATTEMPTS)
		return Poll::CONTINUE;
	param.req.terminate();
	return Poll::DONE;
}

Poll::ret_stt client_read(Poll &p, int fd, int revents, Poll::Param &param)
{
	(void)p;
	(void)fd;
	(void)revents;
	(void)param;
	std::cout << "Client Read" << std::endl;
	if (param.req.getRequestAttempts() >= HTTPRequest::MAX_ATTEMPTS)
		return Poll::DONE;
	param.req.recvRequest();
	try
	{
		param.req.getBasicRequest().parseRaw();
	}
	catch (ABaseHTTPCall::Incomplete &e)
	{
		std::cout << "Request is not finished [" << e.what() << "\n";
		return Poll::CONTINUE;
	}
	catch (ABaseHTTPCall::Invalid &e)
	{
		std::cout << "Request is invalid\n";
		return Poll::DONE;
	}
	param.req.handleRequest();
	p.addWrite(param.client_fd, client_write, param);
	return Poll::DONE;
}

Poll::ret_stt initSocketsHandler(Poll &p, int fd, int revents, Poll::Param &param)
{
	(void)p;
	(void)fd;
	(void)revents;
	(void)param;
	int client_fd = Server::acceptConnection(fd);
	Poll::Param new_param = {HTTPRequest(param.req.getVirtualServer(), client_fd), -1, client_fd, -1, -1};
	p.addRead(client_fd, client_read, new_param);
	return Poll::CONTINUE;
}

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ServerManager::ServerManager(const IConf *conf)
	: _poll()
	, _conf(conf)
	, _status(STOPED)
{
	std::list<const IServerConf *> servers = conf->getServers();
	std::list<const IServerConf *>::iterator it = servers.begin();
	std::list<const IServerConf *>::iterator end = servers.end();
	for (; it != end; it++)
	{
		this->_virtualServers.push_back(Server(*it));
	}
	this->_poll = Poll();
}

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
		std::vector<int> fds = it->getSockets();
		std::vector<int>::iterator it_fds = fds.begin();
		std::vector<int>::iterator end_fds = fds.end();
		for (; it_fds != end_fds; i++, it_fds++)
		{
			Poll::Param param = {HTTPRequest(&(*it), -1), -1, -1, -1, -1};
			this->_poll.addRead(*it_fds, initSocketsHandler, param);
		}
	}
}

void ServerManager::start()
{
	this->_poll.loop();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */

/*
		pollCnt = poll(this->_poll, this->_pollSize, timeOut);
		(void)pollCnt;
		for (int i = 0; i < this->_pollSize; i++)
		{
			if (!this->_poll[i].revents)
				continue;

			//-------- Handle Client Request
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
*/