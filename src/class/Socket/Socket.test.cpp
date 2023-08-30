
#include <Socket/Socket.hpp>
#include <gtest/gtest.h>

TEST(Socket, CreateDestroy)
{
	Listen *listenobj = new Listen("127.0.0.1", "1234");
	Socket *obj = new Socket(listenobj);

	delete obj;
	delete listenobj;
}

TEST(Socket, Accessor)
{
	Listen *listenobj = new Listen("127.0.0.1", "1234");
	Socket obj = Socket(listenobj);
	EXPECT_NE(-1, obj.getFd());
	EXPECT_EQ(htons(1234), htons(obj.getPort().get()));
	EXPECT_EQ(inet_addr("127.0.0.1"), inet_addr(obj.getIp().get().c_str()));
	delete listenobj;
}

TEST(Socket, SocketCreationFailed)
{
	Listen *listenobj = new Listen("127.0.0.1", "1234");
	Socket obj = Socket(listenobj);
	EXPECT_NO_THROW(Socket obj1(obj));
	delete listenobj;
}

TEST(Socket, SocketListeningFailed)
{
	Listen *listenobj = new Listen("127.0.0.1", "1234");
	Socket obj = Socket(listenobj);
	EXPECT_NO_THROW(obj.bind());
	delete listenobj;
}

TEST(Socket, SocketBindingFailed)
{
	Listen *listenobj = new Listen("127.0.0.1", "1234");
	Socket obj = Socket(listenobj);
	EXPECT_THROW(obj.listen(), Socket::SocketNotBinded);
	EXPECT_NO_THROW(obj.bind());
	EXPECT_NO_THROW(obj.listen());
	delete listenobj;
}