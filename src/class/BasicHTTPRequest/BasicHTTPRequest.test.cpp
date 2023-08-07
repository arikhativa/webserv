
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
	BasicHTTPRequest obj(
		"GET /over/there?name=ferret HTTP/1.1\r\nHost: localhost:8081\r\nConnection: keep-alive\r\nsec-ch-ua: "
		"\"Not.A/Brand\";v=\"8\", \"Chromium\";v=\"114\", \"Opera\";v=\"100\"\r\nsec-ch-ua-mobile: "
		"?0\r\nsec-ch-ua-platform: \"Windows\"\r\nDNT: 1\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 "
		"(Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36 "
		"OPR/100.0.0.0\r\nAccept: "
		"text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/"
		"signed-exchange;v=b3;q=0.7\r\nSec-Fetch-Site: none\r\nSec-Fetch-Mode: navigate\r\nSec-Fetch-User: "
		"?1\r\nSec-Fetch-Dest: document\r\nAccept-Encoding: gzip, deflate, br\r\nAccept-Language: en-US,en;q=0.9\r\n");

	EXPECT_EQ(BasicHTTPRequest::GET, obj.getType());
	EXPECT_EQ("/over/there", obj.getPath());
	EXPECT_EQ("?name=ferret", obj.getQuery());
	EXPECT_EQ(BasicHTTPRequest::HTTP_1_1, obj.getHTTPVersion());

	EXPECT_EQ(15, obj.getHeaders().size());
	EXPECT_EQ("localhost:8081", obj.getHeaders().at("Host"));
	EXPECT_EQ("keep-alive", obj.getHeaders().at("Connection"));
	EXPECT_EQ("\"Not.A/Brand\";v=\"8\", \"Chromium\";v=\"114\", \"Opera\";v=\"100\"", obj.getHeaders().at("sec-ch-ua"));
	EXPECT_EQ("?0", obj.getHeaders().at("sec-ch-ua-mobile"));
	EXPECT_EQ("\"Windows\"", obj.getHeaders().at("sec-ch-ua-platform"));
	EXPECT_EQ("1", obj.getHeaders().at("DNT"));
	EXPECT_EQ("1", obj.getHeaders().at("Upgrade-Insecure-Requests"));
	EXPECT_EQ(obj.getHeaders().at("User-Agent"),
			  "Mozilla/5.0 "
			  "(Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36 "
			  "OPR/100.0.0.0");
	EXPECT_EQ(obj.getHeaders().at("Accept"),
			  "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,"
			  "application/"
			  "signed-exchange;v=b3;q=0.7");
	EXPECT_EQ("none", obj.getHeaders().at("Sec-Fetch-Site"));
	EXPECT_EQ("navigate", obj.getHeaders().at("Sec-Fetch-Mode"));
	EXPECT_EQ("?1", obj.getHeaders().at("Sec-Fetch-User"));
	EXPECT_EQ("document", obj.getHeaders().at("Sec-Fetch-Dest"));
	EXPECT_EQ("gzip, deflate, br", obj.getHeaders().at("Accept-Encoding"));
	EXPECT_EQ("en-US,en;q=0.9", obj.getHeaders().at("Accept-Language"));
}

TEST(BasicHTTPRequest, Print)
{
	static const char *res =
		"{\"_type\": \"GET\",\"_path\": \"/over/there\",\"_query\": \"?name=ferret\",\"_http_version\": "
		"\"HTTP/1.1\",\"_headers\": {\"Accept\": "
		"\"text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/"
		"*;q=0.8,application/signed-exchange;v=b3;q=0.7\", \"Accept-Encoding\": \"gzip, deflate, br\", "
		"\"Accept-Language\": \"en-US,en;q=0.9\", \"Connection\": \"keep-alive\", \"DNT\": \"1\", \"Host\": "
		"\"localhost:8081\", \"Sec-Fetch-Dest\": \"document\", \"Sec-Fetch-Mode\": \"navigate\", \"Sec-Fetch-Site\": "
		"\"none\", \"Sec-Fetch-User\": \"?1\", \"Upgrade-Insecure-Requests\": \"1\", \"User-Agent\": \"Mozilla/5.0 "
		"(Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36 "
		"OPR/100.0.0.0\", \"sec-ch-ua\": \"\\\"Not.A/Brand\\\";v=\\\"8\\\", \\\"Chromium\\\";v=\\\"114\\\", "
		"\\\"Opera\\\";v=\\\"100\\\"\", \"sec-ch-ua-mobile\": \"?0\", \"sec-ch-ua-platform\": \"\\\"Windows\\\"\"}}";

	BasicHTTPRequest obj(
		"GET /over/there?name=ferret HTTP/1.1\r\nHost: localhost:8081\r\nConnection: keep-alive\r\nsec-ch-ua: "
		"\"Not.A/Brand\";v=\"8\", \"Chromium\";v=\"114\", \"Opera\";v=\"100\"\r\nsec-ch-ua-mobile: "
		"?0\r\nsec-ch-ua-platform: \"Windows\"\r\nDNT: 1\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 "
		"(Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36 "
		"OPR/100.0.0.0\r\nAccept: "
		"text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/"
		"signed-exchange;v=b3;q=0.7\r\nSec-Fetch-Site: none\r\nSec-Fetch-Mode: navigate\r\nSec-Fetch-User: "
		"?1\r\nSec-Fetch-Dest: document\r\nAccept-Encoding: gzip, deflate, br\r\nAccept-Language: en-US,en;q=0.9\r\n");

	std::stringstream ss;
	ss << obj;
	EXPECT_EQ(res, ss.str());
}
