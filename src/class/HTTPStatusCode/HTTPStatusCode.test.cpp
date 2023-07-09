
#include <HTTPStatusCode/HTTPStatusCode.hpp>
#include <gtest/gtest.h>

TEST(HTTPStatusCode, CreateDestroy)
{
	HTTPStatusCode *obj = new HTTPStatusCode(HTTPStatusCode::Code::OK);
	delete obj;
}

TEST(HTTPStatusCode, Accessor)
{
	HTTPStatusCode obj(HTTPStatusCode::Code::OK);

	EXPECT_EQ(HTTPStatusCode::Code::OK, obj.get());
	obj.set(HTTPStatusCode::Code::NOT_FOUND);
	EXPECT_EQ(HTTPStatusCode::Code::NOT_FOUND, obj.get());
	obj.set(500);
	EXPECT_EQ(HTTPStatusCode::Code::INTERNAL_SERVER_ERROR, obj.get());
}

TEST(HTTPStatusCode, Canonical)
{
	HTTPStatusCode obj1(200);
	HTTPStatusCode obj2(101);
	HTTPStatusCode obj3(obj1);

	EXPECT_EQ(obj1.get(), obj3.get());
	obj2 = obj1;
	EXPECT_EQ(obj1.get(), obj2.get());
}

TEST(HTTPStatusCode, Exception)
{
	EXPECT_THROW(HTTPStatusCode obj(0), HTTPStatusCode::InvalidStatusCodeException);
	EXPECT_THROW(HTTPStatusCode obj(99), HTTPStatusCode::InvalidStatusCodeException);
	EXPECT_THROW(HTTPStatusCode obj(506), HTTPStatusCode::InvalidStatusCodeException);
	HTTPStatusCode obj(200);
	EXPECT_THROW(obj.set(0), HTTPStatusCode::InvalidStatusCodeException);
}

TEST(HTTPStatusCode, toString)
{
	HTTPStatusCode obj1(200);
	HTTPStatusCode obj2(101);
	HTTPStatusCode obj3(500);

	EXPECT_EQ("OK", obj1.toString());
	EXPECT_EQ("Switching Protocols", obj2.toString());
	EXPECT_EQ("Internal Server Error", obj3.toString());
}

TEST(HTTPStatusCode, Print)
{
	HTTPStatusCode obj1(200);
	HTTPStatusCode obj2(101);
	HTTPStatusCode obj3(500);

	std::stringstream ss1;
	std::stringstream ss2;
	std::stringstream ss3;

	ss1 << obj1;
	ss2 << obj2;
	ss3 << obj3;

	EXPECT_EQ("HTTPStatusCode[200 OK]", ss1.str());
	EXPECT_EQ("HTTPStatusCode[101 Switching Protocols]", ss2.str());
	EXPECT_EQ("HTTPStatusCode[500 Internal Server Error]", ss3.str());
}
