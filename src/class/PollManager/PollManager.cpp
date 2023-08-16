
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
	// Set the file descriptor as non-blocking
	fcntl(fd, F_SETFL, O_NONBLOCK);

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

int PollManager::pollFunction(int fd)
{
	std::vector<pollfd>::iterator it = _fds.begin();
	for (; it != _fds.end(); ++it)
	{
		if (it->fd == fd)
			break;
	}
	if (it == _fds.end())
		throw PollManager::PollManagerException();
	int result = ::poll(&(*it), _fds.size(), 0);
	if (result == 0) // this fd doesn't have any event
		return (0);
	if (result < 0) // error
		throw PollManager::PollManagerException();
	// this fd has activity
	return (result);
}

bool PollManager::isInActivity(int fd)
{
	int result = pollFunction(fd);
	std::cout << "result: " << result << std::endl;
	return (result > 0);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */
