
#include <ErrorPageSet/ErrorPageSet.hpp>
#include <gtest/gtest.h>

TEST(ErrorPageSet, CreateDestroy)
{
	ErrorPageSet *obj = new ErrorPageSet();
	delete obj;
}

TEST(ErrorPageSet, Accessor)
{
	ErrorPageSet obj;

	obj.setPage(HTTPStatusCode::Code::OK, "ok.html");

	EXPECT_EQ("/ok.html", obj.getPage(HTTPStatusCode::Code::OK));
}

TEST(ErrorPageSet, Canonical)
{
	ErrorPageSet obj1;
	ErrorPageSet obj2;

	obj1.setPage(HTTPStatusCode::Code::OK, "ok.html");
	obj2.setPage(HTTPStatusCode::Code::ACCEPTED, "accepted.html");

	ErrorPageSet obj3(obj1);

	EXPECT_EQ(obj1.getPage(HTTPStatusCode::Code::OK), obj3.getPage(HTTPStatusCode::Code::OK));
	obj2 = obj1;
	EXPECT_EQ(obj1.getPage(HTTPStatusCode::Code::OK), obj2.getPage(HTTPStatusCode::Code::OK));
}
