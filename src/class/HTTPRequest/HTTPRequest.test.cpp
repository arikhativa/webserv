
#include <HTTPRequest/HTTPRequest.hpp>
#include <gtest/gtest.h>

TEST(HTTPRequest, CreateDestroy)
{
	HTTPRequest *obj = new HTTPRequest(-1);
	delete obj;
}

TEST(HTTPRequest, Accessor)
{
	int fd[2];
	pipe(fd);
	HTTPRequest obj(fd[0]);

	std::string request("GET /");
	EXPECT_EQ(fd[0], obj.getClientFd());
	obj.setRawRequest(request);
	EXPECT_EQ(request, obj.getRawRequest());
	EXPECT_TRUE(obj.getResponse().empty());
	close(fd[0]);
	close(fd[1]);
}

TEST(HTTPRequest, RecievingRequestError)
{
	int fd[2];
	pipe(fd);
	HTTPRequest obj(fd[0]);
	EXPECT_THROW(obj.recvRequest(), HTTPRequest::RecievingRequestError);
	HTTPRequest obj1(-1);
	EXPECT_THROW(obj.recvRequest(), HTTPRequest::RecievingRequestError);
	close(fd[0]);
	close(fd[1]);
}

TEST(HTTPRequest, SendingResponseError)
{
	int fd[2];
	pipe(fd);
	HTTPRequest obj(fd[0]);
	EXPECT_THROW(obj.sendResponse(), HTTPRequest::SendingResponseError);
	HTTPRequest obj1(-1);
	EXPECT_THROW(obj.sendResponse(), HTTPRequest::SendingResponseError);
	close(fd[0]);
	close(fd[1]);
}