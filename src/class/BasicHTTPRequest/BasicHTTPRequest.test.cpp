
#include <BasicHTTPRequest/BasicHTTPRequest.hpp>
#include <gtest/gtest.h>

TEST(BasicHTTPRequest, CreateDestroy)
{
	BasicHTTPRequest *obj = new BasicHTTPRequest("GET / HTTP/1.1");
	delete obj;
}

TEST(BasicHTTPRequest, Canonical)
{
	BasicHTTPRequest obj1("GET / HTTP/1.1\r\nHost: localhost:8081\r\n");
	BasicHTTPRequest obj2("POST / HTTP/1.1\r\nHost: localhost:80\r\n");
	BasicHTTPRequest obj3(obj1);

	EXPECT_EQ(BasicHTTPRequest::GET, obj1.getType());
	EXPECT_EQ(BasicHTTPRequest::POST, obj2.getType());
	EXPECT_EQ(BasicHTTPRequest::GET, obj3.getType());

	obj2 = obj3;
	EXPECT_EQ(BasicHTTPRequest::GET, obj2.getType());
}

TEST(BasicHTTPRequest, Accessor)
{
	BasicHTTPRequest obj("POST /over/there?name=ferret HTTP/1.1\r\nHost: localhost:8081\r\nConnection: "
						 "keep-alive\r\nContent-Length: 10\r\n\r\nabcdefghij");

	obj.setBody();
	EXPECT_EQ(BasicHTTPRequest::POST, obj.getType());
	EXPECT_EQ("/over/there", obj.getPath());
	EXPECT_EQ("?name=ferret", obj.getQuery());
	EXPECT_EQ(BasicHTTPRequest::HTTP_1_1, obj.getHTTPVersion());

	EXPECT_EQ("localhost:8081", obj.getHeaders().at(httpConstants::headers::HOST));
	EXPECT_EQ("keep-alive", obj.getHeaders().at(httpConstants::headers::CONNECTION));
	EXPECT_EQ("10", obj.getHeaders().at(httpConstants::headers::CONTENT_LENGTH));
	EXPECT_EQ("abcdefghij", obj.getBody());
}

TEST(BasicHTTPRequest, Print)
{
	static const char *res = "{\"_type\": \"GET\",\"_path\": \"/over/there\",\"_query\": "
							 "\"?name=ferret\",\"_http_version\": \"HTTP/1.1\",\"_headers\": {\"Connection\": "
							 "\"keep-alive\", \"Host\": \"localhost:8081\", \"Sec-Ch-Ua\": \"\"}}";

	BasicHTTPRequest obj("GET /over/there?name=ferret HTTP/1.1\r\nHost: localhost:8081\r\nConnection: "
						 "keep-alive\r\nsec-ch-ua: \r\n\r\n");

	std::stringstream ss;
	ss << obj;
	EXPECT_EQ(res, ss.str());
}

TEST(BasicHTTPRequest, isChunked)
{
	BasicHTTPRequest obj("POST / HTTP/1.1\r\nTransfer-Encoding: chunked\r\n\r\n4body\r\n0\r\n\r\n");

	EXPECT_TRUE(obj.isChunked());
}

TEST(BasicHTTPRequest, setBody)
{
	BasicHTTPRequest obj("POST / HTTP/1.1\r\nContent-Length: 4\r\n\r\nbody");

	obj.setBody();
	EXPECT_STREQ("body", obj.getBody().c_str());
}

TEST(BasicHTTPRequest, ExceptionDupHeaders)
{
	EXPECT_THROW(BasicHTTPRequest obj("POST / HTTP/1.1\r\nContent-Length: 4\r\nContent-Length: 4\r\n\r\nbody"),
				 BasicHTTPRequest::InvalidRequestException);
}

TEST(BasicHTTPRequest, AppendDupHeaders)
{
	BasicHTTPRequest obj("POST / HTTP/1.1\r\nasd: 4\r\nasd: 4\r\n\r\nbody");

	std::map<std::string, std::string> h = obj.getHeaders();
	EXPECT_STREQ("4, 4", h["Asd"].c_str());
}

TEST(BasicHTTPRequest, toString)
{
	BasicHTTPRequest obj("POST / HTTP/1.1\r\ncontenT-length: 4\r\n\r\nbody");

	obj.setBody();
	EXPECT_STREQ("POST / HTTP/1.1\r\nContent-Length: 4\r\n\r\nbody", obj.toString().c_str());
}
