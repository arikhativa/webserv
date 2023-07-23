
#include <ResponseHeader/ResponseHeader.hpp>
#include <gtest/gtest.h>


TEST(ResponseHeader, CreateDestroy)
{
	ResponseHeader *obj = new ResponseHeader(502);
	delete obj;
}

TEST(ResponseHeader, Create)
{
	ResponseHeader obj(404);
	EXPECT_EQ("404 Not Found", obj.getStatusMessage());
}

TEST(ResponseHeader, StatusMessage)
{
	ResponseHeader obj(300);
	obj.setStatusCode(200);
	EXPECT_EQ("200 OK", obj.getStatusMessage());
}

TEST(ResponseHeader, ExceptionCodeNotFound)
{
	EXPECT_THROW(ResponseHeader obj1(5), ResponseHeader::InvalidCodeStatusException);
}

TEST(ResponseHeader, ContentType)
{
	ResponseHeader obj(404);

	EXPECT_EQ("text/plain", obj.getContentType());
}

TEST(ResponseHeader, ConnectionClose)
{
	ResponseHeader obj(503);

	EXPECT_EQ("close", obj.getConnection());
}

TEST(ResponseHeader, ConnectionOpen)
{
	ResponseHeader obj(200);

	EXPECT_EQ("keep-alive", obj.getConnection());
}