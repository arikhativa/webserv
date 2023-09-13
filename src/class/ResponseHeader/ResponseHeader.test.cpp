
#include <ResponseHeader/ResponseHeader.hpp>
#include <gtest/gtest.h>

TEST(ResponseHeader, CreateDestroy)
{
	ErrorPageSet error_page_set;
	HTTPStatusCode code(404);

	ResponseHeader *obj = new ResponseHeader(code, error_page_set);
	delete obj;
}

TEST(ResponseHeader, Create)
{
	ErrorPageSet error_page_set;

	HTTPStatusCode code(404);
	ResponseHeader obj(code, error_page_set);
	EXPECT_EQ("404 Not Found", obj.getStatusMessage());
}

TEST(ResponseHeader, StatusMessage)
{
	ErrorPageSet error_page_set;

	HTTPStatusCode code(300);
	ResponseHeader obj(code, error_page_set);

	code.set(200);
	obj.setStatusCode(code);
	EXPECT_EQ("200 OK", obj.getStatusMessage());
}

TEST(ResponseHeader, InvalidStatusCodeException)
{
	ErrorPageSet error_page_set;
	HTTPStatusCode code(200);

	ResponseHeader obj(code, error_page_set);

	EXPECT_THROW(obj.setContentType("does not exist"), ContentTypes::InvalidExtensionException);
}

TEST(ResponseHeader, ContentType)
{
	ErrorPageSet error_page_set;
	HTTPStatusCode code(404);
	ResponseHeader obj(code, error_page_set);

	EXPECT_EQ("text/html", obj.getContentType());
}

TEST(ResponseHeader, ConnectionClose)
{
	ErrorPageSet error_page_set;
	HTTPStatusCode code(503);
	ResponseHeader obj(code, error_page_set);

	EXPECT_EQ("close", obj.getConnection());
}

TEST(ResponseHeader, ConnectionOpen)
{
	HTTPStatusCode code(200);
	ErrorPageSet error_page_set;
	ResponseHeader obj(code, error_page_set);

	EXPECT_EQ("keep-alive", obj.getConnection());
}

TEST(ResponseHeader, Default_error_page)
{
	ErrorPageSet error_page_set;
	HTTPStatusCode code(402);
	ResponseHeader obj(code, error_page_set);
	EXPECT_EQ("<!DOCTYPE html>\n<html>\n<body>\n<h1>402 Payment Required</h1>\n</body>\n</html>", obj.getBody());

	code.set(200);
	ResponseHeader obj2(code, error_page_set);
	EXPECT_EQ("", obj2.getBody());

	code.set(502);
	ResponseHeader obj3(code, error_page_set);
	std::size_t header_pos = obj3.getBody().find("<title>502 Bad Gateway</title>");
	EXPECT_NE(std::string::npos, header_pos);
}

TEST(ResponseHeader, Empty_error_page)
{
	ErrorPageSet error_page_set;
	HTTPStatusCode code(404);

	ResponseHeader obj(code, error_page_set);
	std::size_t header_pos = obj.getBody().find("<title>404 Page Not Found</title>");
	EXPECT_NE(std::string::npos, header_pos);

	code.set(200);
	ResponseHeader obj2(code, error_page_set);
	EXPECT_EQ("", obj2.getBody());

	code.set(502);
	ResponseHeader obj3(code, error_page_set);
	header_pos = obj3.getBody().find("<title>502 Bad Gateway</title>");
	EXPECT_NE(std::string::npos, header_pos);
}

TEST(ResponseHeader, error_page_not_found)
{
	HTTPStatusCode code(404);

	ErrorPageSet error_page_set;
	error_page_set.setPage(code.get(), "does not exist");

	EXPECT_THROW(ResponseHeader obj(code, error_page_set), ResponseHeader::InvalidDefaultPage);
}
