
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
	explicit PollManager(void);
	~PollManager();

	class PollManagerException : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};
	class PollTimeoutException : public PollManagerException
	{
	  public:
		virtual const char *what() const throw();
	};

	bool isAvailable(const int &fd, const short &events) const;

  private:
	const pollfd _newFdPoll(int fd, short events) const;
	int _pollFunction(pollfd actual) const;

	static const int TIMEOUT;
	static const int ERROR;
	static const int TIMEOUT_VALUE;
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* POLL_MANAGER_HPP */
