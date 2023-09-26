
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
#include <HTTPCall/HTTPCall.hpp>
#include <HTTPResponse/HTTPResponse.hpp>
#include <IConf/IConf.hpp>
#include <Time/Time.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class Poll
{
  public:
	struct Param
	{
		// setup
		Time start_read;
		const IConf *conf;
		const IListen *src_listen;
		const Socket *src_socket;

		// initSocketsHandler
		HTTPCall call;

		// CGI flow
		int write_pipe;
		int read_pipe;

		Param operator=(const Param &p)
		{
			std::cout << "A: " << std::endl;
			this->start_read = p.start_read;
			this->conf = p.conf;
			this->src_listen = p.src_listen;
			this->src_socket = p.src_socket;
			this->call = p.call;
			this->write_pipe = p.write_pipe;
			this->read_pipe = p.read_pipe;
			return *this;
		}
	};

	enum ret_stt
	{
		ERROR = -1,
		CONTINUE,
		DONE_CLOSE_FD,
		DONE_NO_CLOSE_FD,
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
	static const int _CALL_TIMEOUT_SEC = 5;

	bool _run;
	std::vector< pollfd > _fds;
	std::vector< t_handler > _handlers;
	std::vector< std::string > _buffers;
	std::vector< Param > _params;

	void _pop(std::vector< std::pair< int, ret_stt > > &indexes_to_close);
	void _pop_index(std::pair< int, ret_stt > p);
	void _closeTimeoutCallsIfNeeded(void);
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* POLL_HPP */
