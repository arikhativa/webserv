
#include <ErrorPage/ErrorPage.hpp>
#include <gtest/gtest.h>

TEST(ErrorPage, CreateDestroy)
{
	ErrorPage *obj = new ErrorPage("500", "/internal_error.html");
	delete obj;
}

TEST(ErrorPage, Accessor)
{
	ErrorPage obj(HTTPStatusCode(505), Path("/"));

	EXPECT_EQ(505, obj.getStatus().get());
	EXPECT_EQ("/", obj.getPath().get());

	obj.setPath("/test");
	obj.setStatus(HTTPStatusCode(404));
	EXPECT_EQ(404, obj.getStatus().get());
	EXPECT_EQ("/test", obj.getPath().get());
}

TEST(ErrorPage, Canonical)
{
	ErrorPage obj1("500", "/internal_error.html");
	ErrorPage obj2("404", "/client_error.html");
	ErrorPage obj3(obj1);

	EXPECT_EQ(obj1.getStatus().get(), obj3.getStatus().get());
	EXPECT_EQ(obj1.getPath().get(), obj3.getPath().get());
	obj2 = obj1;
	EXPECT_EQ(obj1.getStatus().get(), obj2.getStatus().get());
	EXPECT_EQ(obj1.getPath().get(), obj2.getPath().get());
}

TEST(ErrorPage, Exception)
{
	EXPECT_THROW(ErrorPage obj2("-5", "/"), HTTPStatusCode::InvalidStatusCodeException);
}

TEST(ErrorPage, Print)
{
	ErrorPage obj("500", "/internal_error.html");

	std::stringstream ss;
	ss << obj;
	EXPECT_EQ("{\"_status\": 500, \"_path\": \"/internal_error.html\"}", ss.str());
}
