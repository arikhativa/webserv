
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
	std::vector<int> pop_indexes;

	while (_run)
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
						pop_indexes.push_back(i);
					else if (ERROR == s)
					{
						std::cerr << "Error on fd " << _fds[i].fd << std::endl;
						pop_indexes.push_back(i);
					}
				}
			}
			_pop(pop_indexes);
		}
	}
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

void Poll::_pop_index(int fd_index)
{
	int fd_to_close = _fds[fd_index].fd;
	int count = 0;

	for (size_t i = 0; i < _fds.size(); ++i)
	{
		if (_fds[i].fd == fd_to_close)
			++count;
	}
	if (count == 1)
	{
		std::cout << "_pop(fd_index): " << fd_index << " close(fd_to_close):" << fd_to_close << std::endl;

		close(fd_to_close);
	}
	else
		std::cout << "_pop(fd_index): " << fd_index << " no close(count):" << count << std::endl;

	_fds.erase(_fds.begin() + fd_index);
	_handlers.erase(_handlers.begin() + fd_index);
}

void Poll::_pop(std::vector<int> &fds_to_close)
{
	for (std::vector<int>::reverse_iterator it = fds_to_close.rbegin(); it != fds_to_close.rend(); ++it)
	{
		_pop_index(*it);
	}
	fds_to_close.clear();
}

/* ************************************************************************** */
