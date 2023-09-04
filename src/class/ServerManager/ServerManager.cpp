
#include <ServerManager/ServerManager.hpp>

/* HANDLERS */

Poll::ret_stt ServerManager::clientWrite(Poll &p, int fd, int revents, Poll::Param &param)
{
	(void)p;
	(void)fd;
	(void)revents;
	(void)param;
	try
	{
		param.req.sendResponse();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		return Poll::DONE;
	}

	if (param.req.getBytesSent() < param.req.getResponse().size())
		return Poll::CONTINUE;
	param.req.terminate();
	return Poll::DONE;
}

Poll::ret_stt ServerManager::clientRead(Poll &p, int fd, int revents, Poll::Param &param)
{
	(void)p;
	(void)fd;
	(void)revents;
	(void)param;
	try
	{
		param.req.recvRequest();
		param.req.getBasicRequest().parseRaw();
	}
	catch (ABaseHTTPCall::Incomplete &e)
	{
		std::cerr << "Request is not finished [" << e.what() << "]\n";
		param.req.getBasicRequest().unParse();
		return Poll::CONTINUE;
	}
	catch (ABaseHTTPCall::Invalid &e)
	{
		std::cerr << "Request is invalid [" << e.what() << "]\n";
		return Poll::DONE;
	}
	catch (HTTPCall::RecievingRequestError &e)
	{
		std::cerr << "Request recv error [" << e.what() << "]\n";
		return Poll::DONE;
	}
	param.req.handleRequest();
	p.addWrite(param.client_fd, ServerManager::clientWrite, param);
	return Poll::DONE;
}

Poll::ret_stt ServerManager::initSocketsHandler(Poll &p, int fd, int revents, Poll::Param &param)
{
	(void)p;
	(void)fd;
	(void)revents;
	(void)param;
	int client_fd;
	try
	{
		client_fd = Server::acceptConnection(fd);
	}
	catch (Server::AcceptingConnectionFailed &e)
	{
		std::cerr << "Acepting connection failed [" << e.what() << "]\n";
		return Poll::CONTINUE;
	}
	Poll::Param new_param = {HTTPCall(param.req.getVirtualServer(), client_fd), -1, client_fd, -1, -1};
	p.addRead(client_fd, ServerManager::clientRead, new_param);
	return Poll::CONTINUE;
}

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ServerManager::ServerManager(const IConf *conf)
	: _poll()
	, _conf(conf)
	, _status(ServerManager::OK)
{
	std::list<const IServerConf *> servers = conf->getServers();
	std::list<const IServerConf *>::iterator it = servers.begin();
	std::list<const IServerConf *>::iterator end = servers.end();
	for (; it != end; it++)
	{
		this->_virtual_servers.push_back(Server(*it));
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

ServerManager::status ServerManager::setup()
{
	if (this->_virtual_servers.empty())
		return ServerManager::INVALID_VIRTUAL_SERVERS;
	std::vector<Server>::iterator it = this->_virtual_servers.begin();
	std::vector<Server>::iterator end = this->_virtual_servers.end();
	for (; it != end; it++)
	{
		try
		{
			it->bindSockets();
			it->listenSockets();
		}
		catch (std::exception &e)
		{
			this->terminate();
			return ServerManager::INVALID_VIRTUAL_SERVERS;
		}
		std::vector<int> fds = it->getSockets();
		std::vector<int>::iterator it_fds = fds.begin();
		std::vector<int>::iterator end_fds = fds.end();
		for (; it_fds != end_fds; it_fds++)
		{
			Poll::Param param = {HTTPCall(&(*it), -1), -1, -1, -1, -1};
			this->_poll.addRead(*it_fds, ServerManager::initSocketsHandler, param);
		}
	}
	return ServerManager::OK;
}

void ServerManager::start()
{
	this->_poll.loop();
}

void ServerManager::terminate()
{
	std::vector<Server>::iterator it = this->_virtual_servers.begin();
	std::vector<Server>::iterator end = this->_virtual_servers.end();
	for (; it != end; it++)
	{
		it->closeSockets();
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */