
#include <Listen/Listen.hpp>
#include <gtest/gtest.h>

TEST(Listen, CreateDestroy)
{
	Listen *obj = new Listen();
	delete obj;
}

TEST(Listen, Accessor)
{
	int val(6);
	Listen obj;

	EXPECT_EQ(val, obj.getValue());
	val = 7;
	obj._setPath(val);
	EXPECT_EQ(val, obj.getValue());
}

TEST(Listen, Canonical)
{
	Listen obj1(1);
	Listen obj2(2);
	Listen obj3(obj1);

	EXPECT_EQ(obj1.getValue(), obj3.getValue());
	obj2 = obj1;
	EXPECT_EQ(obj1.getValue(), obj2.getValue());
}
