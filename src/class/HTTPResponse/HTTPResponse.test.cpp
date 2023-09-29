
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
	EXPECT_EQ("Hello", obj.getBodyAsString());
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
		obj.extenedBin(p2, strlen(p2));
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
		obj.extenedBin(p3, strlen(p3));
	}
	try
	{
		obj.parseBody();
	}
	catch (const ABaseHTTPCall::Incomplete &e)
	{
		obj.extenedRaw(p4);
		obj.extenedBin(p4, strlen(p4));
	}
	obj.parseBody();
	EXPECT_STREQ("HelloWorld", obj.getBodyAsString().c_str());
}
