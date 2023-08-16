
#include <Poll/Poll.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Poll::Poll()
	: _run(true)
{
}

Poll::Poll(const Poll &src)
	: _run(src._run)
	, _fds(src._fds)
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Poll::~Poll()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Poll &Poll::operator=(Poll const &rhs)
{
	if (this != &rhs)
	{
		this->_run = rhs._run;
		this->_fds = rhs._fds;
	}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

// TODO think of error handling
void Poll::loop(void)
{
	std::list<int> pop_fds;
	int qqq = 0;

	while (qqq < 5)
	{
		int stt = poll(_fds.data(), _fds.size(), _TIMEOUT);

		if (stt == -1)
			perror("poll");
		if (stt > 0)
		{
			for (size_t i = 0; i < _fds.size(); ++i)
			{

				if (_fds[i].revents == POLLOUT || _fds[i].revents == POLLIN)
				{
					ret_stt s = _handlers[i](*this, _fds[i].fd, _fds[i].revents);
					if (DONE == s)
					{
						pop_fds.push_back(_fds[i].fd);
					}
					else if (ERROR == s)
					{
						std::cerr << "Error on fd " << _fds[i].fd << std::endl;
						pop_fds.push_back(_fds[i].fd);
					}
				}
			}
			for (std::list<int>::iterator it = pop_fds.begin(); it != pop_fds.end(); ++it)
			{
				_pop(*it);
			}
			pop_fds.clear();
		}
		++qqq;
	}
}

Poll::ret_stt Poll::WriteClient(Poll &p, int fd, int revents)
{
	(void)p;
	(void)revents;
	std::cout << "WriteClient" << std::endl;
	if (revents == POLLOUT)
	{
		std::string msg =
			"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Hello, World!</h1></body></html>\r\n";
		int bytesSent = send(fd, msg.c_str(), msg.length(), 0);
		(void)bytesSent;

		return DONE;
	}
	return CONTINUE;
}

Poll::ret_stt Poll::ReadClient(Poll &p, int fd, int revents)
{
	std::cout << "ReadClient" << std::endl;
	if (revents == POLLIN)
	{
		(void)p;
		char buffer[1000];

		int bytesReceived = recv(fd, buffer, sizeof(buffer), 0);

		if (bytesReceived > 0)
		{
			buffer[bytesReceived] = '\0';
			std::cout << "Received: " << buffer << std::endl;

			p.addWrite(fd, WriteClient);
			return DONE;
		}
		else if (bytesReceived == 0)
		{
			std::cout << "Connection closed by the client" << std::endl;
			return DONE;
		}
		else
		{
			perror("recv");
		}
	}
	return CONTINUE;
}

Poll::ret_stt Poll::newClient(Poll &p, int fd, int revents)
{
	if (revents == POLLIN)
	{
		int clientSocket = accept(fd, NULL, NULL);
		if (clientSocket > 0)
		{
			std::cout << "Client connected" << std::endl;

			// Set non-blocking mode for the client socket
			int flags = fcntl(clientSocket, F_GETFL, 0);
			fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK);
			p.addRead(clientSocket, Poll::ReadClient);
			return CONTINUE;
		}
	}
	return ERROR;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

void Poll::addRead(int fd, t_handler h)
{
	pollfd pfd = {fd, POLLIN, 0};

	std::cout << "addRead(fd):" << fd << std::endl;

	_fds.push_back(pfd);
	_handlers.push_back(h);
}

void Poll::addWrite(int fd, t_handler h)
{
	pollfd pfd = {fd, POLLOUT, 0};

	std::cout << "addWrite(fd):" << fd << std::endl;
	_fds.push_back(pfd);
	_handlers.push_back(h);
}

void Poll::_pop(int fd)
{
	int count = 0;

	for (size_t i = 0; i < _fds.size(); ++i)
	{
		std::cout << "i: " << i << "_fds[i].fd: " << _fds[i].fd << std::endl;

		if (_fds[i].fd == fd)
		{
			++count;
			_fds.erase(_fds.begin() + i);
			_handlers.erase(_handlers.begin() + i);
			--i;
		}
	}
	if (count == 1)
	{
		std::cout << "close(fd):" << fd << std::endl;

		close(fd);
	}
	else
		std::cout << "Error: fd:" << fd << "count: " << count << std::endl;
}

/* ************************************************************************** */
