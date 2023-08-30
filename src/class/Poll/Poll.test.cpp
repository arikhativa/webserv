
#include <Poll/Poll.hpp>
#include <gtest/gtest.h>

static const char *file = "res/tests/Poll/test_file";

TEST(Poll, CreateDestroy)
{
	Poll *obj = new Poll();
	delete obj;
}

static Poll::ret_stt test_handler(Poll &p, int fd, int revents, Poll::Param &param)
{
	(void)p;
	(void)fd;
	(void)revents;
	(void)param;
	return Poll::DONE;
}

TEST(Poll, FreeAll)
{
	int fd0 = open(file, O_CREAT | O_RDWR, 0644);
	int fd1 = open(file, O_CREAT | O_RDWR, 0644);
	int fd2 = open(file, O_CREAT | O_RDWR, 0644);
	{
		Poll p;

		Poll::Param param;

		p.addRead(fd0, test_handler, param);
		p.addWrite(fd1, test_handler, param);
		p.addRead(fd2, test_handler, param);
	}
	int ret = write(fd0, "test", 4);
	EXPECT_EQ(ret, -1);
}

static Poll::ret_stt writeToClient(Poll &p, int fd, int revents, Poll::Param &param)
{
	if (Poll::isWriteEvent(revents))
	{
		// send(fd, param.cgi_
		// res.toString().c_str(), param.cgi_res.toString().size(), 0);
		p.exitLoop();
		return Poll::DONE;
	}

	return Poll::CONTINUE;
}

static Poll::ret_stt readFromCGI(Poll &p, int fd, int revents, Poll::Param &param)
{
	if (Poll::isReadEvent(revents))
	{
		// read(param.read_pipe, buff, sizeof(buff));
		// param.cgi_res.setRaw("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 4\r\n\r\ntest");
		// param.cgi_res.parseRaw();
		// param.cgi_res.parseBody();

		p.addWrite(param.client_fd, writeToClient, param);
		return Poll::DONE;
	}

	return Poll::CONTINUE;
}

static Poll::ret_stt writeToCGI(Poll &p, int fd, int revents, Poll::Param &param)
{
	if (Poll::isWriteEvent(revents))
	{
		// write(param.write_pipe, param.req.toString().c_str(), param.req.toString().size());

		p.addRead(param.read_pipe, readFromCGI, param);
		return Poll::DONE;
	}

	return Poll::CONTINUE;
}

static Poll::ret_stt readFromClient(Poll &p, int fd, int revents, Poll::Param &param)
{
	if (Poll::isReadEvent(revents))
	{
		int fake_client_fd = open(file, O_CREAT | O_RDWR, 0644);

		param.req.setRaw(
			"POST /cgi-bin/test.cgi HTTP/1.1\r\nHost: localhost:8080\r\nContent-Length: 4\r\nContent-Type: "
			"application/x-www-form-urlencoded\r\n\r\ntest");

		param.req.parseRaw();
		param.req.parseBody();

		param.write_pipe = fake_client_fd;
		param.read_pipe = fake_client_fd;
		param.client_fd = fd;

		p.addWrite(param.write_pipe, writeToCGI, param);
		return Poll::DONE;
	}

	return Poll::CONTINUE;
}

static Poll::ret_stt newClient(Poll &p, int fd, int revents, Poll::Param &_)
{
	(void)_;

	if (Poll::isReadEvent(revents))
	{
		int fake_client_fd = open(file, O_CREAT | O_RDWR, 0644);

		Poll::Param param;

		param.src_socket = fd;
		p.addRead(fake_client_fd, readFromClient, param);
	}

	return Poll::CONTINUE;
}

TEST(Poll, HandlerExample)
{
	int fake_socket = open(file, O_CREAT | O_RDWR, 0644);

	{
		Poll p;

		Poll::Param param;
		p.addRead(fake_socket, newClient, param);
		p.loop();
	}
	int ret = write(fake_socket, "test", 4);
	EXPECT_EQ(ret, -1);
}
