
#include <Return/Return.hpp>
#include <gtest/gtest.h>

TEST(Return, CreateDestroy)
{
	Return *obj = new Return("500", "/internal_error.html");
	delete obj;
}

TEST(Return, Accessor)
{
	Return obj(HTTPStatusCode(505), Path("/"));

	EXPECT_EQ(505, obj.getStatus().get());
	EXPECT_EQ("/", obj.getPath().get());

	obj.setPath("/test");
	obj.setStatus(HTTPStatusCode(404));
	EXPECT_EQ(404, obj.getStatus().get());
	EXPECT_EQ("/test", obj.getPath().get());
}

TEST(Return, Canonical)
{
	Return obj1("500", "/internal_error.html");
	Return obj2("404", "/client_error.html");
	Return obj3(obj1);

	EXPECT_EQ(obj1.getStatus().get(), obj3.getStatus().get());
	EXPECT_EQ(obj1.getPath().get(), obj3.getPath().get());
	obj2 = obj1;
	EXPECT_EQ(obj1.getStatus().get(), obj2.getStatus().get());
	EXPECT_EQ(obj1.getPath().get(), obj2.getPath().get());
}

TEST(Return, Exception)
{
	EXPECT_THROW(Return obj2("-5", "/"), HTTPStatusCode::InvalidStatusCodeException);
}

TEST(Return, Print)
{
	Return obj("500", "/internal_error.html");

	std::stringstream ss;
	ss << obj;
	EXPECT_EQ("{\"_status\": 500, \"_path\": \"/internal_error.html\"}", ss.str());
}
