
#include <ServerManager/ServerManager.hpp>

/* HANDLERS */

Poll::ret_stt ServerManager::cgiWrite(Poll &p, int fd, int revents, Poll::Param &param)
{
	(void)fd;
	if (!Poll::isWriteEvent(revents))
		return Poll::CONTINUE;
	try
	{
		if (param.call.getBasicRequest().getType() == BasicHTTPRequest::GET)
		{
			Poll::Param new_param = param;
			new_param.start_read.setToNow();
			p.addRead(param.call.getCgi()->getReadFd(), ServerManager::cgiRead, new_param);
			return Poll::DONE_CLOSE_FD;
		}
		param.call.getCgi()->writeToCgi();
	}
	catch (CgiManager::CgiManagerException &e)
	{
		std::cerr << "CGI writing error [" << e.what() << "]" << std::endl;

		param.call.setInternalServerResponse();
		p.addWrite(param.call.getClientFd(), ServerManager::clientWrite, param);
		close(param.call.getCgi()->getReadFd());
		delete param.call.getCgi();
		return Poll::DONE_CLOSE_FD;
	}
	catch (CgiManager::CgiManagerIncompleteWrite &e)
	{
		return Poll::CONTINUE;
	}

	Poll::Param new_param = param;
	new_param.start_read.setToNow();
	p.addRead(param.call.getCgi()->getReadFd(), ServerManager::cgiRead, new_param);
	return Poll::DONE_CLOSE_FD;
}

Poll::ret_stt ServerManager::cgiRead(Poll &p, int fd, int revents, Poll::Param &param)
{
	(void)fd;
	if (!Poll::isReadEvent(revents) && !Poll::isEOFEvent(revents))
		return Poll::CONTINUE;
	try
	{
		param.call.getCgi()->readFromCgi();
	}
	catch (CgiManager::CgiManagerException &e)
	{
		std::cerr << "CGI reading error [" << e.what() << "]" << std::endl;

		param.call.setInternalServerResponse();
		p.addWrite(param.call.getClientFd(), ServerManager::clientWrite, param);
		delete param.call.getCgi();
		return Poll::DONE_CLOSE_FD;
	}
	catch (CgiManager::CgiManagerIncompleteRead &e)
	{
		param.start_read.setToNow();
		return Poll::CONTINUE;
	}

	param.call.cgiToResponse();
	delete param.call.getCgi();
	p.addWrite(param.call.getClientFd(), ServerManager::clientWrite, param);
	return Poll::DONE_CLOSE_FD;
}

Poll::ret_stt ServerManager::clientWrite(Poll &p, int fd, int revents, Poll::Param &param)
{
	return pollHandler::clientWrite(p, fd, revents, param);
}

Poll::ret_stt ServerManager::clientRead(Poll &p, int fd, int revents, Poll::Param &param)
{
	(void)fd;

	if (!Poll::isReadEvent(revents))
		return Poll::CONTINUE;
	try
	{
		param.call.recvRequest();
		param.call.getBasicRequest().parseRaw();
		if (param.call.getBasicRequest().isBody())
			param.call.getBasicRequest().parseBody();
		std::cout << "[" << fd << "] --> " << param.call << std::endl;
	}
	catch (ABaseHTTPCall::Incomplete &e)
	{
		param.call.getBasicRequest().unParse();

		param.start_read.setToNow();
		return Poll::CONTINUE;
	}
	catch (ABaseHTTPCall::Invalid &e)
	{
		std::cerr << "Request is invalid [" << e.what() << "]" << std::endl;

		param.call.setInvalidResponse();
		param.start_read.reset();
		p.addWrite(param.call.getClientFd(), ServerManager::clientWrite, param);
		return Poll::DONE_CLOSE_FD;
	}
	catch (HTTPCall::ReceivingRequestError &e)
	{
		std::cerr << "Request recv error [" << e.what() << "]" << std::endl;

		param.call.setInternalServerResponse();
		param.start_read.reset();
		p.addWrite(param.call.getClientFd(), ServerManager::clientWrite, param);
		return Poll::DONE_CLOSE_FD;
	}
	catch (HTTPCall::ReceivingRequestEmpty &e)
	{
		std::cerr << "Request recv empty [" << e.what() << "]" << std::endl;
		param.start_read.reset();
		return Poll::DONE_CLOSE_FD;
	}

	param.call.setServerConf(matcher::requestToServer(param.conf, param.src_listen, param.call.getBasicRequest()));
	param.call.setLocation(matcher::requestToLocation(param.call.getServerConf(), param.call.getBasicRequest()));

	if (!param.call.isRequestAllowed())
	{
		param.start_read.reset();
		p.addWrite(param.call.getClientFd(), ServerManager::clientWrite, param);
		return Poll::DONE_CLOSE_FD;
	}

	if (param.call.isRedirect())
	{
		param.start_read.reset();
		p.addWrite(param.call.getClientFd(), ServerManager::clientWrite, param);
		return Poll::DONE_CLOSE_FD;
	}

	param.call.finalizeRequest();

	if ((param.call.isCGI() && !param.call.isCGIValid()) || !param.call.isCGIPostExtValid())
	{
		param.start_read.reset();
		p.addWrite(param.call.getClientFd(), ServerManager::clientWrite, param);
		return Poll::DONE_CLOSE_FD;
	}

	param.call.handleRequest();
	if (param.call.isCGI())
	{
		param.start_read.reset();
		p.addWrite(param.call.getCgi()->getWriteFd(), ServerManager::cgiWrite, param);
		return Poll::DONE_NO_CLOSE_FD;
	}
	else
	{
		param.start_read.reset();
		p.addWrite(param.call.getClientFd(), ServerManager::clientWrite, param);
		return Poll::DONE_CLOSE_FD;
	}
}

Poll::ret_stt ServerManager::initSocketsHandler(Poll &p, int fd, int revents, Poll::Param &param)
{
	if (!Poll::isReadEvent(revents))
		return Poll::CONTINUE;

	int client_fd;
	try
	{
		client_fd = ServerManager::acceptConnection(fd);
	}
	catch (ServerManager::AcceptingConnectionFailed &e)
	{
		std::cerr << "Accepting connection failed [" << e.what() << "]" << std::endl;
		return Poll::CONTINUE;
	}

	std::cout << "New connection\t[" << client_fd << "]"
			  << " from: " << *param.src_socket << std::endl;

	Poll::Param new_param = param;
	new_param.call = HTTPCall(param.src_socket, client_fd);
	new_param.start_read.setToNow();
	fcntl(client_fd, F_SETFL, O_NONBLOCK);
	p.addRead(client_fd, ServerManager::clientRead, new_param);
	return Poll::CONTINUE;
}

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ServerManager::ServerManager(const IConf *conf)
	: _conf(conf)
{
	createServerSockets(conf);
}

const char *ServerManager::ServerCreationFailed::what() const throw()
{
	return "Server creation failed";
}

const char *ServerManager::AcceptingConnectionFailed::what() const throw()
{
	return "Accepting connection failed";
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

void ServerManager::createServerSockets(const IConf *conf)
{
	std::list< const IListen * > listeners;
	std::list< const IServerConf * > servers = conf->getServers();
	std::list< const IServerConf * >::iterator it = servers.begin();
	std::list< const IServerConf * >::iterator end = servers.end();
	for (; it != end; it++)
	{
		std::list< const IListen * > tmpListeners = (*it)->getListen();
		std::list< const IListen * >::iterator it_l = tmpListeners.begin();
		std::list< const IListen * >::iterator end_l = tmpListeners.end();
		for (; it_l != end_l; it_l++)
		{
			try
			{
				Socket new_socket(*it_l);
				std::vector< Socket >::iterator old_socket =
					std::find(this->_sockets.begin(), this->_sockets.end(), new_socket);
				if (old_socket == this->_sockets.end())
					this->_sockets.push_back(new_socket);
			}
			catch (...)
			{
				this->terminate();
				throw;
			}
		}
	}
}

void ServerManager::setup()
{
	if (this->_sockets.empty())
		throw ServerManager::ServerCreationFailed();

	std::vector< Socket >::iterator it = this->_sockets.begin();
	std::vector< Socket >::iterator end = this->_sockets.end();
	for (; it != end; it++)
	{
		try
		{
			it->bind();
			it->listen();
		}
		catch (...)
		{
			this->terminate();
			throw;
		}

		Poll::Param param;

		param.conf = this->_conf;
		param.src_listen = it->getListen();
		param.src_socket = &(*it);

		fcntl(it->getFd(), F_SETFL, O_NONBLOCK);
		this->_poll.addRead(it->getFd(), ServerManager::initSocketsHandler, param);
	}
}

void ServerManager::start()
{
	this->_poll.loop();
}

void ServerManager::terminate()
{
	std::vector< Socket >::iterator it = this->_sockets.begin();
	std::vector< Socket >::iterator end = this->_sockets.end();
	for (; it != end; it++)
		it->close();
}

int ServerManager::acceptConnection(int fd)
{
	int tmp_client;

	tmp_client = accept(fd, NULL, NULL);
	if (tmp_client <= -1)
		throw ServerManager::AcceptingConnectionFailed();
	return tmp_client;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */