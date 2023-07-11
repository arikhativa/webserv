
#include <Socket/Socket.hpp>
#include <gtest/gtest.h>

TEST(Socket, CreateDestroy)
{
	IP ip("127.0.0.1");
	Port port(1234);
	Socket *obj = new Socket(ip, port);
	delete obj;
}

TEST(Socket, Accessor)
{
	IP ip("127.0.0.1");
	Port port(1234);
	Socket obj1(ip, port);
	EXPECT_NE(-1, obj1.getFd());
	EXPECT_EQ(htons(1234), htons(obj1.getPort().get()));
	EXPECT_EQ(inet_addr("127.0.0.1"), inet_addr(obj1.getIp().getAddress().c_str()));
}

TEST(Socket, SocketCreationFailed)
{
	IP ip("127.0.0.1");
	Port port(1234);
	EXPECT_NO_THROW(Socket obj1(ip, port));
}

TEST(Socket, SocketListeningFailed)
{
	IP ip("127.0.0.1");
	Port port(1234);
	Socket obj1(ip, port);
	EXPECT_NO_THROW(obj1.bind());
}

TEST(Socket, SocketBindingFailed)
{
	IP ip("127.0.0.1");
	Port port(1234);
	Socket obj1(ip, port);
	EXPECT_NO_THROW(obj1.listen());
}