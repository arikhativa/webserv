
#include <Port/Port.hpp>
#include <gtest/gtest.h>

TEST(Port, CreateDestroy)
{
	Port *obj = new Port(8080);
	delete obj;
}

TEST(Port, Accessor)
{
	Port obj(8080);

	EXPECT_EQ(8080, obj.get());
	obj.set(9090);
	EXPECT_EQ(9090, obj.get());
}

TEST(Port, Canonical)
{
	Port obj1(1);
	Port obj2(2);
	Port obj3(obj1);

	EXPECT_EQ(obj1.get(), obj3.get());
	obj2 = obj1;
	EXPECT_EQ(obj1.get(), obj2.get());
}

TEST(Port, InvalidPortException)
{
	EXPECT_THROW(Port obj1("0"), Port::InvalidPortException);
	EXPECT_THROW(Port obj2("65536"), Port::InvalidPortException);
	EXPECT_THROW(Port obj3("-1"), Port::InvalidPortException);
}
