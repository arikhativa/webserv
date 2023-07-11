
#include <HTTPRequestHandler/HTTPRequestHandler.hpp>
#include <gtest/gtest.h>

TEST(HTTPRequestHandler, CreateDestroy)
{
	HTTPRequestHandler *obj = new HTTPRequestHandler();
	delete obj;
}

TEST(HTTPRequestHandler, Accessor)
{
	int val(6);
	HTTPRequestHandler obj;

	EXPECT_EQ(val, obj.getValue());
	val = 7;
	obj._setPath(val);
	EXPECT_EQ(val, obj.getValue());
}

TEST(HTTPRequestHandler, Canonical)
{
	HTTPRequestHandler obj1(1);
	HTTPRequestHandler obj2(2);
	HTTPRequestHandler obj3(obj1);

	EXPECT_EQ(obj1.getValue(), obj3.getValue());
	obj2 = obj1;
	EXPECT_EQ(obj1.getValue(), obj2.getValue());
}
