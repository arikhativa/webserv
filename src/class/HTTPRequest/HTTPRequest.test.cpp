
#include <HTTPRequest/HTTPRequest.hpp>
#include <gtest/gtest.h>

TEST(HTTPRequest, CreateDestroy)
{
	HTTPRequest *obj = new HTTPRequest();
	delete obj;
}

TEST(HTTPRequest, Accessor)
{
	int val(6);
	HTTPRequest obj;

	EXPECT_EQ(val, obj.getValue());
	val = 7;
	obj._setPath(val);
	EXPECT_EQ(val, obj.getValue());
}

TEST(HTTPRequest, Canonical)
{
	HTTPRequest obj1(1);
	HTTPRequest obj2(2);
	HTTPRequest obj3(obj1);

	EXPECT_EQ(obj1.getValue(), obj3.getValue());
	obj2 = obj1;
	EXPECT_EQ(obj1.getValue(), obj2.getValue());
}
