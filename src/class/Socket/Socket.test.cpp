
#include <Socket/Socket.hpp>
#include <gtest/gtest.h>

TEST(Socket, CreateDestroy)
{
	Socket *obj = new Socket();
	delete obj;
}

TEST(Socket, Accessor)
{
	int val(6);
	Socket obj;

	EXPECT_EQ(val, obj.getValue());
	val = 7;
	obj._setPath(val);
	EXPECT_EQ(val, obj.getValue());
}

TEST(Socket, Canonical)
{
	Socket obj1(1);
	Socket obj2(2);
	Socket obj3(obj1);

	EXPECT_EQ(obj1.getValue(), obj3.getValue());
	obj2 = obj1;
	EXPECT_EQ(obj1.getValue(), obj2.getValue());
}
