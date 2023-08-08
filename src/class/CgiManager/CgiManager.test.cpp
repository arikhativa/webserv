
#include <CgiManager/CgiManager.hpp>
#include <gtest/gtest.h>

TEST(CgiManager, CreateDestroy)
{
	BasicHTTPRequest basicHTTPRequest("GET / HTTP/1.1\r\nHost: localhost:8080\r\nUser-Agent: Mozilla/5.0\r\nAccept: text/html\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\n\r\n");
	Path pathCGI("/usr/bin/python3");
	std::string serverName("serverName");
	std::string port("1234");
	CgiManager *obj = new CgiManager(basicHTTPRequest, pathCGI, serverName, port);
	delete obj;
}

/*
TEST(CgiManager, Accessor)
{
	int val(6);
	CgiManager obj;

	EXPECT_EQ(val, obj.getValue());
	val = 7;
	obj._setPath(val);
	EXPECT_EQ(val, obj.getValue());
}*/

TEST(CgiManager, Canonical)
{
	BasicHTTPRequest basicHTTPRequest("GET / HTTP/1.1\r\nHost: localhost:8080\r\nUser-Agent: Mozilla/5.0\r\nAccept: text/html\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\n\r\n");
	Path pathCGI("/usr/bin/python3");
	std::string serverName("serverName");
	std::string port("1234");

	CgiManager obj1(basicHTTPRequest, pathCGI, serverName, port);

	EXPECT_EQ(obj1.getServerName(), "serverName");
	EXPECT_EQ(obj1.getPort(), "1234");
	EXPECT_EQ(obj1.getPathCGI().get(), "/usr/bin/python3");
}

TEST(CgiManager, setCgiManager)
{
	BasicHTTPRequest basicHTTPRequest("POST /res/get_hello.py?first_name=pepe&last_name=juan HTTP/1.1\r\nHost: localhost:8080\r\nUser-Agent: Mozilla/5.0\r\nAccept: text/html\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\n\r\n");
	Path pathCGI("/usr/bin/python3");
	std::string serverName("serverName");
	std::string port("1234");


	CgiManager obj1(basicHTTPRequest, pathCGI, serverName, port);
	std::string content = obj1.setCgiManager();

	EXPECT_EQ(content, "pepe\n");
}

TEST(CgiManager, envCgi)
{
	BasicHTTPRequest basicHTTPRequest("POST /res/env.py?pepe=juan HTTP/1.1\r\nHost: localhost:8080\r\nUser-Agent: Mozilla/5.0\r\nAccept: text/html\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\n\r\n");
	Path pathCGI("/usr/bin/python3");
	std::string serverName("serverName");
	std::string port("1234");

	CgiManager obj1(basicHTTPRequest, pathCGI, serverName, port);
	std::string content = obj1.setCgiManager();

	EXPECT_EQ(content, "pepe=juan\n");
}

TEST(CgiManager, waitCgi)
{
	BasicHTTPRequest basicHTTPRequest("POST /res/form.py?name=juan&Email=juan@gmail.com&Message=Hello HTTP/1.1\r\nHost: localhost:8080\r\nUser-Agent: Mozilla/5.0\r\nAccept: text/html\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\n\r\n");
	Path pathCGI("/usr/bin/python3");
	std::string serverName("serverName");
	std::string port("1234");

	CgiManager obj1(basicHTTPRequest, pathCGI, serverName, port);
	std::string content = obj1.setCgiManager();

	EXPECT_EQ(content, "\n");
}