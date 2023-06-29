
#include <gtest/gtest.h>
#include <ExampleClass/ExampleClass.hpp>

TEST(ExampleClass, CreateDestroy)
{
	ExampleClass *obj = new ExampleClass();
	delete obj;
}

TEST(ExampleClass, getValue)
{
	int val(6);
	ExampleClass i(val);
	EXPECT_EQ(val, i.getValue());
}

TEST(ExampleClass, _setValue)
{
	ExampleClass i;
	i._setValue(7);
	EXPECT_EQ(i.getValue(), 7);
}
