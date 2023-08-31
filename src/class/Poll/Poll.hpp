
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

#include <BasicHTTPRequest/BasicHTTPRequest.hpp>
#include <HTTPRequest/HTTPRequest.hpp>
#include <HTTPResponse/HTTPResponse.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class Poll
{
  public:
	struct Param
	{
		// general
		HTTPRequest req;
		int src_socket;
		int client_fd;

		// CGI flow
		int write_pipe;
		int read_pipe;
	};

	enum ret_stt
	{
		ERROR = -1,
		CONTINUE,
		DONE,
	};

	typedef ret_stt (*t_handler)(Poll &p, int fd, int revents, Param &param);

	Poll();
	~Poll();
	Poll(const Poll &src);

	Poll &operator=(Poll const &rhs);

	void loop(void);
	void addRead(int fd, t_handler h, Param p);
	void addWrite(int fd, t_handler h, Param p);
	void exitLoop(void);
	static bool isReadEvent(int revents);
	static bool isWriteEvent(int revents);

  private:
	static const int _TIMEOUT = 10000;

	bool _run;
	std::vector<pollfd> _fds;
	std::vector<t_handler> _handlers;
	std::vector<std::string> _buffers;
	std::vector<Param> _params;

	void _pop(std::vector<int> &indexes_to_close);
	void _pop_index(int i);
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* POLL_HPP */