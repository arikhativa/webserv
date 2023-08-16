
#ifndef POLL_HPP
#define POLL_HPP

#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <list>
#include <poll.h>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <vector>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class Poll
{
  public:
	enum ret_stt
	{
		ERROR = -1,
		CONTINUE,
		DONE,
	};
	typedef ret_stt (*t_handler)(Poll &p, int fd, int revents);

	Poll();
	~Poll();
	Poll(const Poll &src);

	Poll &operator=(Poll const &rhs);

	void loop(void);
	void addRead(int fd, t_handler h);
	void addWrite(int fd, t_handler h);

	static ret_stt newClient(Poll &p, int fd, int revents);
	static ret_stt ReadClient(Poll &p, int fd, int revents);
	static ret_stt WriteClient(Poll &p, int fd, int revents);

  private:
	static const int _TIMEOUT = 1000;

	bool _run;
	std::vector<pollfd> _fds;
	std::vector<t_handler> _handlers;

	void _pop(int fd);
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* POLL_HPP */
