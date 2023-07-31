
#include <AllowedMethods/AllowedMethods.hpp>
#include <gtest/gtest.h>

TEST(AllowedMethods, CreateDestroy)
{
	AllowedMethods *obj = new AllowedMethods();
	delete obj;
}

TEST(AllowedMethods, Accessor)
{
	AllowedMethods obj;

	EXPECT_EQ(false, obj.getGET());
	EXPECT_EQ(false, obj.getPOST());
	EXPECT_EQ(false, obj.getDELETE());
	obj.setGET(true);
	obj.setPOST(true);
	obj.setDELETE(true);
	EXPECT_EQ(true, obj.getGET());
	EXPECT_EQ(true, obj.getPOST());
	EXPECT_EQ(true, obj.getDELETE());
}

TEST(AllowedMethods, Canonical)
{
	std::list<std::string> m1;
	std::list<std::string> m2;

	m1.push_back(AllowedMethods::GET);
	m2.push_back(AllowedMethods::POST);

	AllowedMethods obj1(m1);
	AllowedMethods obj2(m2);
	AllowedMethods obj3(obj1);

	EXPECT_EQ(obj1.isAllowed(IAllowedMethods::GET), obj3.isAllowed(IAllowedMethods::GET));
	EXPECT_EQ(obj1.isAllowed(IAllowedMethods::POST), obj3.isAllowed(IAllowedMethods::POST));
	EXPECT_EQ(obj1.isAllowed(IAllowedMethods::DELETE), obj3.isAllowed(IAllowedMethods::DELETE));
	obj2 = obj1;
	EXPECT_EQ(obj1.isAllowed(IAllowedMethods::GET), obj2.isAllowed(IAllowedMethods::GET));
	EXPECT_EQ(obj1.isAllowed(IAllowedMethods::POST), obj2.isAllowed(IAllowedMethods::POST));
	EXPECT_EQ(obj1.isAllowed(IAllowedMethods::DELETE), obj2.isAllowed(IAllowedMethods::DELETE));
}

TEST(AllowedMethods, Exception)
{
	std::list<std::string> m;

	m.push_back("HEY");
	EXPECT_THROW(AllowedMethods obj(m), AllowedMethods::InvalidMethodException);
}

TEST(AllowedMethods, isAllowed)
{
	std::list<std::string> m;

	m.push_back(AllowedMethods::POST);
	AllowedMethods obj(m);
	EXPECT_EQ(false, obj.isAllowed(IAllowedMethods::GET));
	EXPECT_EQ(true, obj.isAllowed(IAllowedMethods::POST));
	EXPECT_EQ(false, obj.isAllowed(IAllowedMethods::DELETE));
}

TEST(AllowedMethods, PrintPost)
{
	std::list<std::string> m;

	m.push_back(AllowedMethods::POST);
	AllowedMethods obj(m);
	std::stringstream ss;
	ss << obj;
	EXPECT_EQ("AllowedMethods[POST]", ss.str());
}

TEST(AllowedMethods, PrintAll)
{
	std::list<std::string> m;

	m.push_back(AllowedMethods::GET);
	m.push_back(AllowedMethods::POST);
	m.push_back(AllowedMethods::DELETE);
	AllowedMethods obj(m);
	std::stringstream ss;
	ss << obj;
	EXPECT_EQ("AllowedMethods[GET, POST, DELETE]", ss.str());
}
