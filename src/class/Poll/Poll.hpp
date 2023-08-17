
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
	typedef ret_stt (*t_handler)(Poll &p, int fd, int revents, void *call);

	Poll();
	~Poll();
	Poll(const Poll &src);

	Poll &operator=(Poll const &rhs);

	void loop(void);
	void addRead(int fd, t_handler h, void *call);
	void addWrite(int fd, t_handler h, void *call);

  private:
	static const int _TIMEOUT = 10000;

	bool _run;
	std::vector<pollfd> _fds;
	std::vector<t_handler> _handlers;
	std::vector<std::string> _buffers;

	void _pop(std::vector<int> &fds_to_close);
	void _pop_index(int i);
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* POLL_HPP */
