
#include <Replace/Replace.hpp>
#include <gtest/gtest.h>

TEST(Replace, CreateDestroy)
{
	Replace *obj = new Replace();
	delete obj;
}

TEST(Replace, Canonical)
{
	Replace obj1(1);
	Replace obj2(2);
	Replace obj3(obj1);

	EXPECT_EQ(obj1.getValue(), obj3.getValue());
	obj2 = obj1;
	EXPECT_EQ(obj1.getValue(), obj2.getValue());
}

TEST(Replace, getValue)
{
	int val(6);
	Replace obj(val);
	EXPECT_EQ(val, obj.getValue());
}

TEST(Replace, _setValue)
{
	Replace obj;
	obj._setValue(7);
	EXPECT_EQ(obj.getValue(), 7);
}
