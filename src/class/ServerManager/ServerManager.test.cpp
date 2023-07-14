
#include <ServerManager/ServerManager.hpp>
#include <gtest/gtest.h>

TEST(ServerManager, CreateDestroy)
{
	ServerManager *obj = new ServerManager();
	delete obj;
}

TEST(ServerManager, Accessor)
{
	int val(6);
	ServerManager obj;

	EXPECT_EQ(val, obj.getValue());
	val = 7;
	obj._setPath(val);
	EXPECT_EQ(val, obj.getValue());
}

TEST(ServerManager, Canonical)
{
	ServerManager obj1(1);
	ServerManager obj2(2);
	ServerManager obj3(obj1);

	EXPECT_EQ(obj1.getValue(), obj3.getValue());
	obj2 = obj1;
	EXPECT_EQ(obj1.getValue(), obj2.getValue());
}
