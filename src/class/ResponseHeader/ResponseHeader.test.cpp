
#include <ResponseHeader/ResponseHeader.hpp>
#include <gtest/gtest.h>

TEST(ResponseHeader, CreateDestroy)
{
	ErrorPage default_page("404", "/404.html");
	HTTPStatusCode code(502);
	ResponseHeader *obj = new ResponseHeader(code, default_page);
	delete obj;
}

TEST(ResponseHeader, Create)
{
	ErrorPage default_page("200", "/200.html");
	HTTPStatusCode code(404);
	ResponseHeader obj(code, default_page);
	EXPECT_EQ("404 Not Found", obj.getStatusMessage());
}

TEST(ResponseHeader, StatusMessage)
{
	ErrorPage default_page("404", "/404.html");
	HTTPStatusCode code(300);
	ResponseHeader obj(code, default_page);

	code.set(200);
	obj.setStatusCode(code);
	EXPECT_EQ("200 OK", obj.getStatusMessage());
}

TEST(ResponseHeader, InvalidStatusCodeException)
{
	ErrorPage default_page("404", "/404.html");

	HTTPStatusCode code(200);
	ResponseHeader obj(code, default_page);
	EXPECT_THROW(obj.setContentType("does not exist"), ContentTypes::InvalidExtensionException);
}

TEST(ResponseHeader, ContentType)
{
	HTTPStatusCode code(404);
	ErrorPage default_page("200", "/200.html");
	ResponseHeader obj(code, default_page);

	EXPECT_EQ("text/html", obj.getContentType());
}

TEST(ResponseHeader, ConnectionClose)
{
	HTTPStatusCode code(503);
	ErrorPage default_page("404", "/404.html");
	ResponseHeader obj(code, default_page);

	EXPECT_EQ("close", obj.getConnection());
}

TEST(ResponseHeader, ConnectionOpen)
{
	HTTPStatusCode code(200);
	ErrorPage default_page("404", "/404.html");
	ResponseHeader obj(code, default_page);

	EXPECT_EQ("keep-alive", obj.getConnection());
}

TEST(ResponseHeader, Default_error_page)
{

	HTTPStatusCode code(404);
	ErrorPage default_page("400", "/400.html");
	ResponseHeader obj(code, default_page);
	EXPECT_EQ("<!DOCTYPE html>\n<html>\n<body>\n<h1>404 Not Found</h1>\n</body>\n</html>", obj.getBody());

	code.set(200);
	ResponseHeader obj2(code, default_page);
	EXPECT_EQ("", obj2.getBody());

	code.set(502);
	ResponseHeader obj3(code, default_page);
	EXPECT_EQ("<!DOCTYPE html>\n<html>\n<body>\n<h1>502 Bad Gateway</h1>\n</body>\n</html>", obj3.getBody());
}
