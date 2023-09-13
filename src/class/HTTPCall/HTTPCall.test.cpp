
#include <HTTPCall/HTTPCall.hpp>
#include <gtest/gtest.h>

// TEST(HTTPCall, CreateDestroy)
// {
// 	HTTPCall *obj = new HTTPCall(-1);
// 	delete obj;
// }

// TEST(HTTPCall, Accessor)
// {
// 	int fd[2];
// 	pipe(fd);
// 	HTTPCall obj(fd[0]);

// 	std::string request("GET /");
// 	EXPECT_EQ(fd[0], obj.getClientFd());
// 	obj.setRawRequest(request);
// 	EXPECT_EQ(request, obj.getRawRequest());
// 	EXPECT_TRUE(obj.getResponse().empty());
// 	close(fd[0]);
// 	close(fd[1]);
// }

// TEST(HTTPCall, ReceivingRequestError)
// {
// 	int fd[2];
// 	pipe(fd);
// 	HTTPCall obj(fd[0]);
// 	EXPECT_THROW(obj.recvRequest(), HTTPCall::ReceivingRequestError);
// 	HTTPCall obj1(-1);
// 	EXPECT_THROW(obj.recvRequest(), HTTPCall::ReceivingRequestError);
// 	close(fd[0]);
// 	close(fd[1]);
// }

// TEST(HTTPCall, SendingResponseError)
// {
// 	int fd[2];
// 	pipe(fd);
// 	HTTPCall obj(fd[0]);
// 	EXPECT_THROW(obj.sendResponse(), HTTPCall::SendingResponseError);
// 	HTTPCall obj1(-1);
// 	EXPECT_THROW(obj.sendResponse(), HTTPCall::SendingResponseError);
// 	close(fd[0]);
// 	close(fd[1]);
// }