
#include <BasePairCodePath/BasePairCodePath.hpp>
#include <gtest/gtest.h>

TEST(BasePairCodePath, CreateDestroy)
{
	BasePairCodePath *obj = new BasePairCodePath("500", "/internal_error.html");
	delete obj;
}

TEST(BasePairCodePath, Accessor)
{
	BasePairCodePath obj(HTTPStatusCode(505), Path("/"));

	EXPECT_EQ(505, obj.getStatus().get());
	EXPECT_EQ("/", obj.getPath().get());

	obj.setPath("/test");
	obj.setStatus(HTTPStatusCode(404));
	EXPECT_EQ(404, obj.getStatus().get());
	EXPECT_EQ("/test", obj.getPath().get());
}

TEST(BasePairCodePath, Canonical)
{
	BasePairCodePath obj1("500", "/internal_error.html");
	BasePairCodePath obj2("404", "/client_error.html");
	BasePairCodePath obj3(obj1);

	EXPECT_EQ(obj1.getStatus().get(), obj3.getStatus().get());
	EXPECT_EQ(obj1.getPath().get(), obj3.getPath().get());
	obj2 = obj1;
	EXPECT_EQ(obj1.getStatus().get(), obj2.getStatus().get());
	EXPECT_EQ(obj1.getPath().get(), obj2.getPath().get());
}

TEST(BasePairCodePath, Exception)
{
	EXPECT_THROW(BasePairCodePath obj2("-5", "/"), HTTPStatusCode::InvalidStatusCodeException);
}
