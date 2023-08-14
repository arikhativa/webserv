
#include <PollManager/PollManager.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

PollManager::PollManager()
{
}

const char *PollManager::PollManagerException::what() const throw()
{
	return "PollManagerException";
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

PollManager::~PollManager()
{
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void PollManager::addFd(int fd, short events)
{
	struct pollfd newFd;

	newFd.fd = fd;
	newFd.events = events;
	_fds.push_back(newFd);
}

void PollManager::removeFd(int fd)
{
	for (std::vector<pollfd>::iterator it = _fds.begin(); it != _fds.end(); ++it)
	{
		if (it->fd == fd)
		{
			_fds.erase(it);
			return;
		}
	}
	throw PollManager::PollManagerException();
}

int PollManager::poll(void)
{
	return ::poll(&_fds[0], _fds.size(), 0);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */
