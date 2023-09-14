
#include <ServerManager/ServerManager.hpp>

/* HANDLERS */

Poll::ret_stt ServerManager::cgiWrite(Poll &p, int fd, int revents, Poll::Param &param)
{
	(void)p;
	(void)fd;
	(void)revents;
	(void)param;
	// _pipe.setParent();
	// if (_basicHTTPRequest.isBody())
	write(param.write_pipe, param.call.getBasicRequest().getBody().c_str(),
		  param.call.getBasicRequest().getBody().length());
	// ::write(_inputPipe[OUTPUT], str.c_str(), str.length());
	// writeToPipe(_basicHTTPRequest.getBody());
	// _pipe.closeInput();
	// return (_readCgiOutput(pid));
	std::cout << "CGI writting" << std::endl;
	return Poll::DONE;
}

Poll::ret_stt ServerManager::cgiRead(Poll &p, int fd, int revents, Poll::Param &param)
{
	(void)p;
	(void)fd;
	(void)revents;
	(void)param;
	size_t bytes_read = 0;
	int BUFFER_SIZE = 1024;
	char buffer[BUFFER_SIZE];
	std::size_t pos;
	int contentLenght;
	int _exit_status;
	std::string _output = "";

	waitpid(param.call.getCgi()->getPid(), &_exit_status, 0);
	while ((bytes_read = read(param.read_pipe, buffer, sizeof(buffer))) > 0)
	{
	std::cout << "TEST\n";
		_output.append(buffer, bytes_read);
		if ((pos = _output.find(httpConstants::CONTENT_LENGHT_FIELD_KEY)) != std::string::npos)
		{
			std::string content_length = _output.substr(pos + httpConstants::CONTENT_LENGHT_FIELD_KEY.length());
			if ((pos = content_length.find(httpConstants::FIELD_BREAK)) != std::string::npos)
				contentLenght = converter::stringToInt(content_length.substr(0, pos));
			pos = _output.find(httpConstants::HEADER_BREAK);
			if ((pos != std::string::npos) &&
				_output.substr(pos + httpConstants::HEADER_BREAK.length()).length() >= (size_t)contentLenght)
			{
				_output = _output.substr(0, pos + httpConstants::HEADER_BREAK.length() + contentLenght);
				break;
			}
		}
	}
	std::cout << "CGI has read:\n" << _output << std::endl;
	return Poll::DONE;
}

Poll::ret_stt ServerManager::clientWrite(Poll &p, int fd, int revents, Poll::Param &param)
{
	(void)p;
	(void)fd;
	if (!Poll::isWriteEvent(revents))
		return Poll::CONTINUE;
	try
	{
		param.call.sendResponse();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		return Poll::DONE;
	}

	if (param.call.getBytesSent() < param.call.getResponse().size())
		return Poll::CONTINUE;
	param.call.terminate();
	return Poll::DONE;
}

Poll::ret_stt ServerManager::clientEntryPoint(Poll &p, int fd, int revents, Poll::Param &param)
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
	}
	catch (ABaseHTTPCall::Incomplete &e)
	{
		std::cerr << "Request is not finished [" << e.what() << "]\n";
		param.call.getBasicRequest().unParse();
		return Poll::CONTINUE;
	}
	catch (ABaseHTTPCall::Invalid &e)
	{
		std::cerr << "Request is invalid [" << e.what() << "]\n";
		return Poll::DONE;
	}
	catch (HTTPCall::ReceivingRequestError &e)
	{
		std::cerr << "Request recv error [" << e.what() << "]\n";
		return Poll::DONE;
	}
	catch (HTTPCall::ReceivingRequestEmpty &e)
	{
		return Poll::DONE;
	}

	param.call.setServerConf(matcher::requestToServer(param.conf, param.src_listen, param.call.getBasicRequest()));
	param.call.setLocation(matcher::requestToLocation(param.call.getServerConf(), param.call.getBasicRequest()));

	param.call.handleRequest();
	if (param.call.getCgi())
	{
		std::cout << "Is CGI" << std::endl;
		Poll::Param new_param = {
			param.conf,
			param.src_listen,
			param.src_socket,
			param.call,
			param.call.getCgi()->getWriteFd(),
			param.call.getCgi()->getReadFd(),
		};
		p.addWrite(param.call.getCgi()->getWriteFd(), ServerManager::cgiWrite, new_param);
		p.addRead(param.call.getCgi()->getReadFd(), ServerManager::cgiRead, new_param);
	}
	else
	{
		std::cout << "Is NOT CGI" << std::endl;
		p.addWrite(param.call.getClientFd(), ServerManager::clientWrite, param);
	}
	return Poll::DONE;
}

Poll::ret_stt ServerManager::initSocketsHandler(Poll &p, int fd, int revents, Poll::Param &param)
{
	if (!Poll::isReadEvent(revents))
		return Poll::CONTINUE;

	int client_fd;
	try
	{
		client_fd = Server::acceptConnection(fd);
	}
	catch (Server::AcceptingConnectionFailed &e)
	{
		std::cerr << "Accepting connection failed [" << e.what() << "]\n";
		return Poll::CONTINUE;
	}
	Poll::Param new_param = {
		param.conf,
		param.src_listen,
		param.src_socket,
		HTTPCall(param.call.getVirtualServer(), param.call.getSocket(), client_fd),
		-1,
		-1,
	};
	p.addRead(client_fd, ServerManager::clientEntryPoint, new_param);
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
		this->_virtual_servers.push_back(new Server(*it));
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

	std::vector<Server *>::iterator it = this->_virtual_servers.begin();
	std::vector<Server *>::iterator end = this->_virtual_servers.end();
	for (; it != end; it++)
	{
		try
		{
			(*it)->bindSockets();
			(*it)->listenSockets();
		}
		catch (std::exception &e)
		{
			this->terminate();
			return ServerManager::INVALID_VIRTUAL_SERVERS;
		}
		std::vector<int> fds = (*it)->getSocketsFd();
		const std::vector<Socket *> sock = (*it)->getSockets();
		std::vector<int>::iterator it_fds = fds.begin();
		std::vector<int>::iterator end_fds = fds.end();

		std::vector<Socket *>::const_iterator it_sock = sock.begin();
		std::vector<Socket *>::const_iterator end_sock = sock.end();
		for (; it_fds != end_fds && it_sock != end_sock; it_fds++, it_sock++)
		{
			Poll::Param param = {this->_conf, (*it_sock)->getListen(), *it_fds, HTTPCall(*it, *it_sock, -1), -1, -1};
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
	std::vector<Server *>::iterator it = this->_virtual_servers.begin();
	std::vector<Server *>::iterator end = this->_virtual_servers.end();
	for (; it != end; it++)
	{
		(*it)->closeSockets();
		delete *it;
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */