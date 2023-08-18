
#include <IP/IP.hpp>
#include <gtest/gtest.h>

TEST(IP, CreateDestroy)
{
	IP *obj = new IP("1.2.3.4");
	delete obj;
}

TEST(IP, Accessor)
{
	{
		std::string str = "0.0.0.0";
		IP obj(str);

		EXPECT_EQ(str, obj.get());
		str = "1.2.3.4";
		obj.setAddress(str);
		EXPECT_EQ(str, obj.get());
	}
	{
		std::string str = "6.6.6.6";
		IP obj(str);

		EXPECT_EQ(str, obj.get());
	}
}

TEST(IP, Canonical)
{
	IP obj1("1.1.1.1");
	IP obj2("2.2.2.2");
	IP obj3(obj1);

	EXPECT_NE(obj1.get(), obj2.get());
	EXPECT_EQ(obj1.get(), obj3.get());
	obj2 = obj1;
	EXPECT_EQ(obj1.get(), obj2.get());
}

TEST(IP, Valid)
{
	EXPECT_THROW(
		{
			try
			{
				IP obj("invalid ip");
			}
			catch (const IP::InvalidIPException &e)
			{
				EXPECT_STREQ("Invalid IP address", e.what());
				throw;
			}
		},
		IP::InvalidIPException);
	EXPECT_THROW(
		{
			try
			{
				IP obj("256.256.256.256");
			}
			catch (const IP::InvalidIPException &e)
			{
				EXPECT_STREQ("Invalid IP address", e.what());
				throw;
			}
		},
		IP::InvalidIPException);
	EXPECT_THROW(
		{
			try
			{
				IP obj(".2.2.2");
			}
			catch (const IP::InvalidIPException &e)
			{
				EXPECT_STREQ("Invalid IP address", e.what());
				throw;
			}
		},
		IP::InvalidIPException);
	EXPECT_THROW(
		{
			try
			{
				IP obj("255.255..255");
			}
			catch (const IP::InvalidIPException &e)
			{
				EXPECT_STREQ("Invalid IP address", e.what());
				throw;
			}
		},
		IP::InvalidIPException);
}
