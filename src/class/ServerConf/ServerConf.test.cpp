
#include <ServerConf/ServerConf.hpp>
#include <gtest/gtest.h>

// TEST(ServerConf, CreateDestroy)
// {
// 	ServerConf *obj = new ServerConf();
// 	delete obj;
// }
TEST(ServerConf, CreateDestroy)
{
	ServerConf obj;

	obj.setName("name");
	std::cout << obj << std::endl;
}

// TEST(ServerConf, Accessor)
// {
// 	int val(6);
// 	ServerConf obj;

// 	EXPECT_EQ(val, obj.getValue());
// 	val = 7;
// 	obj._setPath(val);
// 	EXPECT_EQ(val, obj.getValue());
// }

// TEST(ServerConf, Canonical)
// {
// 	ServerConf obj1(1);
// 	ServerConf obj2(2);
// 	ServerConf obj3(obj1);

// 	EXPECT_EQ(obj1.getValue(), obj3.getValue());
// 	obj2 = obj1;
// 	EXPECT_EQ(obj1.getValue(), obj2.getValue());
// }
