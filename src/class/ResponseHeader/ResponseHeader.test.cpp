
#include <ResponseHeader/ResponseHeader.hpp>
#include <gtest/gtest.h>

TEST(ResponseHeader, CreateDestroy)
{
	ErrorPage default_page("404", "/404.html");
	ResponseHeader *obj = new ResponseHeader(502, default_page);
	delete obj;
}

TEST(ResponseHeader, Create)
{
	ErrorPage default_page("200", "/200.html");
	ResponseHeader obj(404, default_page);
	EXPECT_EQ("404 Not Found", obj.getStatusMessage());
}

TEST(ResponseHeader, StatusMessage)
{
	ErrorPage default_page("404", "/404.html");
	ResponseHeader obj(300, default_page);
	obj.setStatusCode(200);
	EXPECT_EQ("200 OK", obj.getStatusMessage());
}

TEST(ResponseHeader, ExceptionCodeNotFound)
{
	ErrorPage default_page("404", "/404.html");
	EXPECT_THROW(ResponseHeader obj1(5, default_page), HTTPStatusCode::InvalidStatusCodeException);
	EXPECT_THROW(ResponseHeader obj1(-5, default_page), HTTPStatusCode::InvalidStatusCodeException);
	EXPECT_THROW(ResponseHeader obj1(-200, default_page), HTTPStatusCode::InvalidStatusCodeException);
	EXPECT_THROW(ResponseHeader obj1(299, default_page), HTTPStatusCode::InvalidStatusCodeException);

	EXPECT_THROW(ResponseHeader obj1(404, default_page), ResponseHeader::InvalidDefaultPage);
}

TEST(ResponseHeader, ContentType)
{
	ErrorPage default_page("200", "/200.html");
	ResponseHeader obj(404, default_page);

	EXPECT_EQ("text/html", obj.getContentType());
}

TEST(ResponseHeader, ConnectionClose)
{
	ErrorPage default_page("404", "/404.html");
	ResponseHeader obj(503, default_page);

	EXPECT_EQ("close", obj.getConnection());
}

TEST(ResponseHeader, ConnectionOpen)
{
	ErrorPage default_page("404", "/404.html");
	ResponseHeader obj(200, default_page);

	EXPECT_EQ("keep-alive", obj.getConnection());
}

TEST(ResponseHeader, Default_error_page)
{
	ErrorPage default_page("400", "/400.html");
	ResponseHeader obj(404, default_page);
	EXPECT_EQ("<!DOCTYPE html>\n<html>\n<body>\n<h1>404 Not Found</h1>\n</body>\n</html>", obj.getBody());
	ResponseHeader obj2(200, default_page);
	EXPECT_EQ("", obj2.getBody());
	ResponseHeader obj3(502, default_page);
	EXPECT_EQ("<!DOCTYPE html>\n<html>\n<body>\n<h1>502 Bad Gateway</h1>\n</body>\n</html>", obj3.getBody());
}
