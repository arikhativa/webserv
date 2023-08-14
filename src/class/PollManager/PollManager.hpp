
#ifndef POLL_MANAGER_HPP
#define POLL_MANAGER_HPP

#include <algorithm>
#include <fcntl.h>
#include <iostream>
#include <poll.h>
#include <string>
#include <vector>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class PollManager
{
  public:
	PollManager(void);
	~PollManager();

	class PollManagerException : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

	void addFd(int fd, short events);
	void removeFd(int fd);
	int poll(void);

  private:
	std::vector<pollfd> _fds;
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* POLL_MANAGER_HPP */
