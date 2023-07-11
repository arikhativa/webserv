
#include <HTTPRequest/HTTPRequest.hpp>
#include <gtest/gtest.h>

TEST(HTTPRequest, CreateDestroy)
{
	HTTPRequest *obj = new HTTPRequest(-1);
	delete obj;
}

TEST(HTTPRequest, Accessor)
{
	int fd(6);
	HTTPRequest obj(fd);

	/* Simple getter*/
	std::string request("GET /");
	EXPECT_EQ(fd, obj.getClientFd());
	obj.setRawRequest(request);
	EXPECT_EQ(request, obj.getRawRequest());
	EXPECT_TRUE(obj.getResponse().empty());
}

TEST(HTTPRequest, Canonical)
{
	HTTPRequest obj1(1);
	HTTPRequest obj2(2);
	HTTPRequest obj3(obj1);

	std::string request("GET /");
	obj1.setRawRequest(request);
	EXPECT_EQ(obj1.getClientFd(), obj3.getClientFd());
	obj2 = obj1;
	EXPECT_EQ(obj1.getClientFd(), obj2.getClientFd());
	EXPECT_EQ(obj1.getRawRequest(), obj2.getRawRequest());
}
