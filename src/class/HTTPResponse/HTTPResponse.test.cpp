
#include <HTTPResponse/HTTPResponse.hpp>
#include <gtest/gtest.h>

TEST(HTTPResponse, CreateDestroy)
{
	HTTPResponse *obj =
		new HTTPResponse("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 5\r\n\r\nHello");
	delete obj;
}

TEST(HTTPResponse, Accessor)
{
	HTTPResponse obj("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 5\r\n\r\nHello");
	obj.parseRaw();
	if (obj.isBody())
		obj.parseBody();
	EXPECT_EQ(HTTPResponse::HTTP_1_1, obj.getHTTPVersion());
	EXPECT_EQ(HTTPStatusCode::OK, obj.getStatusCode().get());
	EXPECT_EQ("text/plain", obj.getHeaders().at(httpConstants::headers::CONTENT_TYPE));
	EXPECT_EQ("5", obj.getHeaders().at(httpConstants::headers::CONTENT_LENGTH));
	EXPECT_EQ("Hello", obj.getBody());
}

TEST(HTTPResponse, Canonical)
{
	HTTPResponse obj1("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 5\r\n\r\nHello");
	HTTPResponse obj2("HTTP/1.1 303 See Other\r\nContent-Type: text/plain\r\nContent-Length: 5\r\n\r\nHello");

	obj1.parseRaw();
	if (obj1.isBody())
		obj1.parseBody();
	obj2.parseRaw();
	if (obj2.isBody())
		obj2.parseBody();

	HTTPResponse obj3(obj1);

	EXPECT_EQ(HTTPStatusCode::OK, obj1.getStatusCode().get());
	EXPECT_EQ(HTTPStatusCode::SEE_OTHER, obj2.getStatusCode().get());
	EXPECT_EQ(HTTPStatusCode::OK, obj3.getStatusCode().get());

	obj2 = obj3;
	EXPECT_EQ(HTTPStatusCode::OK, obj2.getStatusCode().get());
}

TEST(HTTPResponse, ExceptionBadHTTPVersion)
{
	HTTPResponse obj("HTTP/a.a 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 5\r\n\r\nHello");

	EXPECT_THROW(obj.parseRaw(), ABaseHTTPCall::Invalid);
}

TEST(HTTPResponse, ExceptionStatusCode)
{
	HTTPResponse obj("HTTP/1.1 OK\r\nContent-Type: text/plain\r\nContent-Length: 5\r\n\r\nHello");
	EXPECT_THROW(obj.parseRaw(), HTTPStatusCode::InvalidStatusCodeException);
}

TEST(HTTPResponse, ExceptionMissingFirstLine)
{
	HTTPResponse obj("Content-Type: text/plain\r\nContent-Length: 5\r\n\r\nHello");
	EXPECT_THROW(obj.parseRaw(), ABaseHTTPCall::Incomplete);
}

TEST(HTTPResponse, toString)
{
	const char *str = "HTTP/1.1 200 OK\r\nContent-Length: 5\r\nContent-Type: text/plain\r\n\r\nHello";
	HTTPResponse obj(str);

	obj.parseRaw();
	if (obj.isBody())
		obj.parseBody();

	EXPECT_STREQ(str, obj.toString().c_str());
}

TEST(HTTPResponse, appendMultiReads)
{
	const char *p1 = "HTTP/1.1";
	const char *p2 = " 200 OK\r\nContent-Length: 10\r\nContent-Type: text/plain\r\n\r\n";
	const char *p3 = "Hello";
	const char *p4 = "World";

	HTTPResponse obj(p1);
	try
	{
		obj.parseRaw();
	}
	catch (const ABaseHTTPCall::Incomplete &e)
	{
		obj.extenedRaw(p2);
		obj.unParse();
	}
	obj.parseRaw();
	try
	{
		if (obj.isBody())
			obj.parseBody();
	}
	catch (const ABaseHTTPCall::Incomplete &e)
	{
		obj.extenedRaw(p3);
	}
	try
	{
		obj.parseBody();
	}
	catch (const ABaseHTTPCall::Incomplete &e)
	{
		obj.extenedRaw(p4);
	}
	obj.parseBody();
	EXPECT_STREQ("HelloWorld", obj.getBody().c_str());
}

TEST(HTTPResponse, appendMultiReadsChunked)
{
	const char *p1 = "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\nContent-Type: text/plain\r\n\r\n5";
	const char *p2 = "\r\nHello\r\n";
	const char *p3 = "5\r\nWorld\r\n";
	const char *p4 = "0\r\n\r\n";

	HTTPResponse obj(p1);

	obj.parseRaw();

	if (!obj.isBody())
		ASSERT_EXIT(1, ::testing::ExitedWithCode(1), "isBody() == false");

	try
	{
		obj.parseBody();
	}
	catch (const ABaseHTTPCall::Incomplete &e)
	{
		EXPECT_STREQ("5", obj.getRawBody().c_str());
	}
	if (!obj.isChunked())
		ASSERT_EXIT(1, ::testing::ExitedWithCode(1), "isChunked() == false");

	obj.extenedRaw(p2);
	EXPECT_STREQ(p2, obj.getLastExtention().c_str());
	obj.extenedRaw(p3);
	EXPECT_STREQ(p3, obj.getLastExtention().c_str());
	obj.extenedRaw(p4);
	EXPECT_STREQ(p4, obj.getLastExtention().c_str());

	obj.parseBody();
	EXPECT_STREQ("5\r\nHello\r\n5\r\nWorld\r\n0\r\n\r\n", obj.getBody().c_str());
}
