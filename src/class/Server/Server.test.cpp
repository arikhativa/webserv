
#include <Server/Server.hpp>
#include <gtest/gtest.h>

TEST(Server, CreateDestroy)
{
	Server *obj = new Server();
	delete obj;
}

TEST(Server, Accessor)
{
	int val(6);
	Server obj;

	EXPECT_EQ(val, obj.getValue());
	val = 7;
	obj._setPath(val);
	EXPECT_EQ(val, obj.getValue());
}

TEST(Server, Canonical)
{
	Server obj1(1);
	Server obj2(2);
	Server obj3(obj1);

	EXPECT_EQ(obj1.getValue(), obj3.getValue());
	obj2 = obj1;
	EXPECT_EQ(obj1.getValue(), obj2.getValue());
}
