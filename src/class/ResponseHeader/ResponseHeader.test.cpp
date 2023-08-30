
#include <ResponseHeader/ResponseHeader.hpp>
#include <gtest/gtest.h>

TEST(ResponseHeader, CreateDestroy)
{
	std::list<const IErrorPage *> error_pages;
	ErrorPage default_page("404", "res/404.html");
	error_pages.push_back(&default_page);
	HTTPStatusCode code(502);
	ResponseHeader *obj = new ResponseHeader(code, error_pages);
	delete obj;
}

TEST(ResponseHeader, Create)
{
	std::list<const IErrorPage *> error_pages;
	ErrorPage default_page("200", "res/200.html");
	error_pages.push_back(&default_page);
	HTTPStatusCode code(404);
	ResponseHeader obj(code, error_pages);
	EXPECT_EQ("404 Not Found", obj.getStatusMessage());
}

TEST(ResponseHeader, StatusMessage)
{
	std::list<const IErrorPage *> error_pages;
	ErrorPage default_page("404", "res/404.html");
	error_pages.push_back(&default_page);
	HTTPStatusCode code(300);
	ResponseHeader obj(code, error_pages);

	code.set(200);
	obj.setStatusCode(code);
	EXPECT_EQ("200 OK", obj.getStatusMessage());
}

TEST(ResponseHeader, InvalidStatusCodeException)
{
	std::list<const IErrorPage *> error_pages;
	ErrorPage default_page("404", "res/404.html");
	error_pages.push_back(&default_page);
	HTTPStatusCode code(200);
	ResponseHeader obj(code, error_pages);
	EXPECT_THROW(obj.setContentType("does not exist"), ContentTypes::InvalidExtensionException);
}

TEST(ResponseHeader, ContentType)
{
	std::list<const IErrorPage *> error_pages;
	HTTPStatusCode code(404);
	ErrorPage default_page("200", "res/200.html");
	error_pages.push_back(&default_page);
	ResponseHeader obj(code, error_pages);

	EXPECT_EQ("text/html", obj.getContentType());
}

TEST(ResponseHeader, ConnectionClose)
{
	std::list<const IErrorPage *> error_pages;
	HTTPStatusCode code(503);
	ErrorPage default_page("404", "res/404.html");
	error_pages.push_back(&default_page);
	ResponseHeader obj(code, error_pages);

	EXPECT_EQ("close", obj.getConnection());
}

TEST(ResponseHeader, ConnectionOpen)
{
	HTTPStatusCode code(200);
	std::list<const IErrorPage *> error_pages;
	ErrorPage default_page("404", "res/404.html");
	error_pages.push_back(&default_page);
	ResponseHeader obj(code, error_pages);

	EXPECT_EQ("keep-alive", obj.getConnection());
}

TEST(ResponseHeader, Default_error_page)
{

	std::list<const IErrorPage *> error_pages;
	HTTPStatusCode code(404);
	ErrorPage default_page("400", "res/400.html");
	ErrorPage default_page2("404", "res/404.html");
	ErrorPage default_page3("500", "res/500.html");

	error_pages.push_back(&default_page);
	error_pages.push_back(&default_page2);
	error_pages.push_back(&default_page3);
	ResponseHeader obj(code, error_pages);
	EXPECT_EQ("<div id=\"main\">\n\t<div class=\"fof\">\n\t\t\t<h1>Error 404</h1>\n\t</div>\n</div>", obj.getBody());

	code.set(200);
	ResponseHeader obj2(code, error_pages);
	EXPECT_EQ("", obj2.getBody());

	code.set(502);
	ResponseHeader obj3(code, error_pages);
	EXPECT_EQ("<!DOCTYPE html>\n<html>\n<body>\n<h1>502 Bad Gateway</h1>\n</body>\n</html>", obj3.getBody());
}

TEST(ResponseHeader, Empty_error_page)
{

	std::list<const IErrorPage *> error_pages;
	HTTPStatusCode code(404);

	ResponseHeader obj(code, error_pages);
	EXPECT_EQ("<!DOCTYPE html>\n<html>\n<body>\n<h1>404 Not Found</h1>\n</body>\n</html>", obj.getBody());

	code.set(200);
	ResponseHeader obj2(code, error_pages);
	EXPECT_EQ("", obj2.getBody());

	code.set(502);
	ResponseHeader obj3(code, error_pages);
	EXPECT_EQ("<!DOCTYPE html>\n<html>\n<body>\n<h1>502 Bad Gateway</h1>\n</body>\n</html>", obj3.getBody());
}

TEST(ResponseHeader, error_page_not_found)
{
	HTTPStatusCode code(404);

	std::list<const IErrorPage *> error_pages;
	ErrorPage default_page("404", "res/40.html");
	error_pages.push_back(&default_page);

	EXPECT_THROW(ResponseHeader obj(code, error_pages), ResponseHeader::InvalidDefaultPage);
}