
#include <Socket/Socket.hpp>
#include <gtest/gtest.h>

TEST(Socket, CreateDestroy)
{
	Listen *listenobj;
	listenobj->setAddress("127.0.0.1");
	listenobj->setPort("443");
	Socket *obj = new Socket(listenobj);

	delete obj;
}

TEST(Socket, Accessor)
{
	Listen *listenobj;
	listenobj->setAddress("127.0.0.1");
	listenobj->setPort("443");
	Socket obj = Socket(listenobj);
	EXPECT_NE(-1, obj.getFd());
	EXPECT_EQ(htons(1234), htons(obj.getPort().get()));
	EXPECT_EQ(inet_addr("127.0.0.1"), inet_addr(obj.getIp().get().c_str()));
}

TEST(Socket, SocketCreationFailed)
{
	Listen *listenobj;
	listenobj->setAddress("127.0.0.1");
	listenobj->setPort("443");
	Socket obj = Socket(listenobj);
	EXPECT_NO_THROW(Socket obj1(obj));
}

TEST(Socket, SocketListeningFailed)
{
	Listen *listenobj;
	listenobj->setAddress("127.0.0.1");
	listenobj->setPort("443");
	Socket obj = Socket(listenobj);
	EXPECT_NO_THROW(obj.bind());
}

TEST(Socket, SocketBindingFailed)
{
	Listen *listenobj;
	listenobj->setAddress("127.0.0.1");
	listenobj->setPort("443");
	Socket obj = Socket(listenobj);
	EXPECT_THROW(obj.listen(), Socket::SocketNotBinded);
	EXPECT_NO_THROW(obj.bind());
	EXPECT_NO_THROW(obj.listen());
}