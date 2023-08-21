
#include <PollManager/PollManager.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

const int PollManager::TIMEOUT(5000);
const int PollManager::ERROR(0);
const int PollManager::TIMEOUT_VALUE(0);

PollManager::PollManager()
{
}

const char *PollManager::PollManagerException::what() const throw()
{
	return "PollManagerException";
}

const char *PollManager::PollTimeoutException::what() const throw()
{
	return "PollTimeoutException";
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

const pollfd PollManager::_newFdPoll(int fd, short events) const
{
	// Set the file descriptor as non-blocking
	fcntl(fd, F_SETFL, O_NONBLOCK);

	pollfd newFd;
	newFd.fd = fd;
	newFd.events = events;
	return (newFd);
}

int PollManager::_pollFunction(pollfd actual) const
{
	int result = ::poll(&actual, 1, TIMEOUT);
	if (result == TIMEOUT_VALUE)
		throw PollManager::PollTimeoutException();
	if (result < ERROR)
		throw PollManager::PollManagerException();
	return (actual.revents);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

bool PollManager::isAvailable(const int &fd, const short &events) const
{
	pollfd actual = _newFdPoll(fd, events);
	int status = _pollFunction(actual);

	if ((events & POLLIN) && (status & POLLIN)) // Readable
		return true;
	else if ((events & POLLOUT) && (status & POLLOUT)) // Writable
		return true;
	else // Not readable or writable
		return false;
}

/* ************************************************************************** */
