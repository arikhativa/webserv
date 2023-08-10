
#include <CgiManager/CgiManager.hpp>
#include <gtest/gtest.h>

TEST(CgiManager, CreateDestroy)
{
	BasicHTTPRequest basicHTTPRequest("GET / HTTP/1.1\r\nHost: localhost:8080\r\nUser-Agent: Mozilla/5.0\r\nAccept: "
									  "text/html\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, "
									  "deflate\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\n\r\n");
	Path pathCGI("/usr/bin/python3");
	std::string serverName("serverName");
	std::string port("1234");
	CgiManager *obj = new CgiManager(basicHTTPRequest, pathCGI, serverName, port);
	delete obj;
}

TEST(CgiManager, Canonical)
{
	BasicHTTPRequest basicHTTPRequest("GET / HTTP/1.1\r\nHost: localhost:8080\r\nUser-Agent: Mozilla/5.0\r\nAccept: "
									  "text/html\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, "
									  "deflate\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\n\r\n");
	Path pathCGI("/usr/bin/python3");
	std::string serverName("serverName");
	std::string port("1234");

	CgiManager obj1(basicHTTPRequest, pathCGI, serverName, port);

	EXPECT_EQ(obj1.getServerName(), "serverName");
	EXPECT_EQ(obj1.getPort(), "1234");
	EXPECT_EQ(obj1.getPathCGI().get(), "/usr/bin/python3");
}

TEST(CgiManager, simplecgi)
{
	BasicHTTPRequest basicHTTPRequest(
		"POST /res/get_hello.py?first_name=pepe&last_name=juan HTTP/1.1\r\nHost: localhost:8080\r\nUser-Agent: "
		"Mozilla/5.0\r\nAccept: text/html\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, "
		"deflate\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\n\r\n");
	Path pathCGI("/usr/bin/python3");
	std::string serverName("serverName");
	std::string port("1234");
	Path serverPath(".");

	CgiManager obj1(basicHTTPRequest, pathCGI, serverName, port);
	std::string content = "Content-type: text/html\r\n"
						  "Content-Length: 58\r\n\r\n\n"
						  "<html>\n"
						  "<body>\n"
						  "<h2>Hello, pepe juan!</h2>\n"
						  "</body>\n"
						  "</html>\n";

	EXPECT_EQ(content, obj1.setCgiManager(serverPath));
}

TEST(CgiManager, envCgi)
{
	BasicHTTPRequest basicHTTPRequest(
		"POST /res/env.py?pepe=juan HTTP/1.1\r\nHost: localhost:8080\r\nUser-Agent: Mozilla/5.0\r\nAccept: "
		"text/html\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate\r\nConnection: "
		"keep-alive\r\nUpgrade-Insecure-Requests: 1\r\n\r\n");
	Path pathCGI("/usr/bin/python3");
	std::string serverName("serverName");
	std::string port("1234");
	Path serverPath(".");

	CgiManager obj1(basicHTTPRequest, pathCGI, serverName, port);
	std::string content = obj1.setCgiManager(serverPath);

	EXPECT_EQ(content, "pepe=juan\n");
}

TEST(CgiManager, envFormCgi)
{
	BasicHTTPRequest basicHTTPRequest("POST /res/form.py?name=juan&Email=juan@gmail.com&Message=Hello "
									  "HTTP/1.1\r\nHost: localhost:8080\r\nUser-Agent: Mozilla/5.0\r\nAccept: "
									  "text/html\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, "
									  "deflate\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\n\r\n");
	Path pathCGI("/usr/bin/python3");
	std::string serverName("serverName");
	std::string port("1234");
	Path serverPath(".");

	CgiManager obj1(basicHTTPRequest, pathCGI, serverName, port);
	std::string content = "Content-type: text/html\r\n"
						  "Content-Length: 119\r\n\r\n\n"
						  "<html>\n"
						  "<body>\n"
						  "<h1>Form Data</h1>\n"
						  "<p>Name: juan</p>\n"
						  "<p>Email: juan@gmail.com</p>\n"
						  "<p>Message: Hello</p>\n"
						  "</body>\n"
						  "</html>\n";

	EXPECT_EQ(content, obj1.setCgiManager(serverPath));
}

TEST(CgiManager, formContentCgi)
{
	BasicHTTPRequest basicHTTPRequest(
		"POST /res/formSimple.py "
		"HTTP/1.1\r\nHost: localhost:8080\r\nContent-Length: 14\r\nUser-Agent: Mozilla/5.0\r\nAccept: "
		"text/html\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, "
		"deflate\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\n\r\nthis is a test");
	basicHTTPRequest.setBody();
	Path pathCGI("/usr/bin/python3");
	std::string serverName("serverName");
	std::string port("1234");
	Path serverPath(".");

	CgiManager obj1(basicHTTPRequest, pathCGI, serverName, port);

	EXPECT_EQ("this is a test", basicHTTPRequest.getBody());
	EXPECT_EQ("this is a test\n", obj1.setCgiManager(serverPath));
}

TEST(CgiManager, contentLengthCgi)
{
	BasicHTTPRequest basicHTTPRequest("POST /res/content_length.py "
									  "HTTP/1.1\r\nHost: localhost:8080\r\nUser-Agent: Mozilla/5.0\r\nAccept: "
									  "text/html\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, "
									  "deflate\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\n\r\n");
	Path pathCGI("/usr/bin/python3");
	std::string serverName("serverName");
	std::string port("1234");
	Path serverPath(".");

	CgiManager obj1(basicHTTPRequest, pathCGI, serverName, port);
	std::string expected = "Content-type: text/plain\r\n"
						   "Content-Length: 37\r\n\r\n"
						   "this is a test for the content_length";

	EXPECT_EQ(expected, obj1.setCgiManager(serverPath));
}

TEST(CgiManager, phpCgi)
{
	BasicHTTPRequest basicHTTPRequest(
		"POST /res/simple.php "
		"HTTP/1.1\r\nHost: localhost:8080\r\nContent-Length: 19\r\nUser-Agent: Mozilla/5.0\r\nAccept: "
		"text/html\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, "
		"deflate\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\n\r\nnombre=Juan&edad=25");
	basicHTTPRequest.setBody();
	Path pathCGI("/usr/bin/php");
	std::string serverName("serverName");
	std::string port("1234");
	Path serverPath(".");

	CgiManager obj1(basicHTTPRequest, pathCGI, serverName, port);

	EXPECT_EQ("nombre=Juan&edad=25", basicHTTPRequest.getBody());
	EXPECT_EQ("nombre=Juan&edad=25", obj1.setCgiManager(serverPath));
}
