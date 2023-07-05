
#include <Token/Token.hpp>
#include <gtest/gtest.h>

TEST(Token, CreateDestroy)
{
	Token *obj = new Token();
	delete obj;
}

TEST(Token, Accessor)
{
	int val(6);
	Token obj;

	EXPECT_EQ(val, obj.getValue());
	val = 7;
	obj._setPath(val);
	EXPECT_EQ(val, obj.getValue());
}

TEST(Token, Canonical)
{
	Token obj1(1);
	Token obj2(2);
	Token obj3(obj1);

	EXPECT_EQ(obj1.getValue(), obj3.getValue());
	obj2 = obj1;
	EXPECT_EQ(obj1.getValue(), obj2.getValue());
}
