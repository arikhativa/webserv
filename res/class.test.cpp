
#include <Replace/Replace.hpp>
#include <gtest/gtest.h>

TEST(Replace, CreateDestroy)
{
	Replace *obj = new Replace();
	delete obj;
}

TEST(Replace, getValue)
{
	int val(6);
	Replace i(val);
	EXPECT_EQ(val, i.getValue());
}

TEST(Replace, _setValue)
{
	Replace i;
	i._setValue(7);
	EXPECT_EQ(i.getValue(), 7);
}
