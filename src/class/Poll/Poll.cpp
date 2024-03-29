
#include <Poll/Poll.hpp>

bool Poll::_run = true;

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Poll::Poll()
{
}

Poll::Poll(const Poll &src)
	: _fds(src._fds)
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Poll::~Poll()
{
	std::pair< int, ret_stt > p;
	p.second = DONE_CLOSE_FD;

	size_t i = _fds.size();

	if (!i)
		return;
	if (i)
		--i;
	while (i)
	{
		p.first = i;
		_pop_index(p);
		--i;
	}
	if (!i)
	{
		p.first = i;
		_pop_index(p);
	}
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Poll &Poll::operator=(Poll const &rhs)
{
	if (this != &rhs)
	{
		this->_fds = rhs._fds;
	}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void Poll::exitLoop(void)
{
	Poll::_run = false;
}

void Poll::_closeTimeoutCallsIfNeeded(void)
{
	std::pair< int, ret_stt > p;
	p.second = DONE_CLOSE_FD;

	for (size_t i = 0; i < _fds.size(); ++i)
	{
		if (_params[i].start_read.isOn())
		{
			if (_params[i].start_read.hasSecondsPassed(_CALL_TIMEOUT_SEC))
			{
				std::cout << "Timeout on fd[" << _fds[i].fd << "]" << std::endl;
				if (_params[i].call.getCgi() != NULL)
					if (_params[i].call.isCGI())
					{
						_params[i].call.setInternalServerResponse();
						addWrite(_params[i].call.getClientFd(), pollHandler::clientWrite, _params[i]);
					}
				p.first = i;
				_pop_index(p);
			}
		}
	}
}

void Poll::loop(void)
{
	std::pair< int, ret_stt > p;
	std::vector< std::pair< int, ret_stt > > pop_indexes;

	while (_run)
	{
		int stt = poll(_fds.data(), _fds.size(), _TIMEOUT);

		if (stt == -1)
		{
			std::cerr << "poll() error" << std::endl;
		}
		else if (stt == 0)
		{
			_closeTimeoutCallsIfNeeded();
		}
		else if (stt > 0)
		{
			for (size_t i = 0; i < _fds.size(); ++i)
			{
				if (_fds[i].revents & POLLOUT || _fds[i].revents & POLLIN || _fds[i].revents & POLLHUP)
				{
					ret_stt s = _handlers[i](*this, _fds[i].fd, _fds[i].revents, _params[i]);
					p.first = i;
					p.second = s;
					if (DONE_CLOSE_FD == s || DONE_NO_CLOSE_FD == s)
						pop_indexes.push_back(p);
					else if (ERROR == s)
					{
						std::cerr << "Error handling fd: " << _fds[i].fd << std::endl;
						pop_indexes.push_back(p);
					}
				}
			}
			_pop(pop_indexes);
		}
	}
}

bool Poll::isEOFEvent(int revents)
{
	return revents & POLLHUP;
}

bool Poll::isReadEvent(int revents)
{
	return revents & POLLIN;
}

bool Poll::isWriteEvent(int revents)
{
	return revents & POLLOUT;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

void Poll::addRead(int fd, t_handler h, Param p)
{
	pollfd pfd = {fd, POLLIN, 0};

	_fds.push_back(pfd);
	_handlers.push_back(h);
	_params.push_back(p);
}

void Poll::addWrite(int fd, t_handler h, Param p)
{
	pollfd pfd = {fd, POLLOUT, 0};

	_fds.push_back(pfd);
	_handlers.push_back(h);
	_params.push_back(p);
}

void Poll::_pop_index(std::pair< int, ret_stt > p)
{
	int fd_to_close = _fds[p.first].fd;
	int count = 0;

	for (size_t i = 0; i < _fds.size(); ++i)
	{
		if (_fds[i].fd == fd_to_close)
			++count;
	}
	if (count == 1 && (p.second == DONE_CLOSE_FD || p.second == ERROR))
	{
		std::cout << "End connection\t[" << fd_to_close << "]" << std::endl;

		close(fd_to_close);
	}

	_fds.erase(_fds.begin() + p.first);
	_handlers.erase(_handlers.begin() + p.first);
	_params.erase(_params.begin() + p.first);
}

void Poll::_pop(std::vector< std::pair< int, ret_stt > > &indexes_to_close)
{
	std::vector< std::pair< int, ret_stt > >::reverse_iterator it = indexes_to_close.rbegin();
	for (; it != indexes_to_close.rend(); ++it)
		_pop_index(*it);
	indexes_to_close.clear();
}

/* ************************************************************************** */
