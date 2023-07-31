
#include <Path/Path.hpp>
#include <gtest/gtest.h>

TEST(Path, CreateDestroy)
{
	Path *obj = new Path();
	delete obj;
}

TEST(Path, Canonical)
{
	Path obj1("path1");
	Path obj2("path2");
	Path obj3(obj1);

	EXPECT_EQ(obj1.get(), obj3.get());
	obj2 = obj1;
	EXPECT_EQ(obj1.get(), obj2.get());
}

TEST(Path, Accessor)
{
	{
		std::string str = "";
		Path obj;

		EXPECT_EQ(str, obj.get());
		str = "test";
		obj.set(str);
		EXPECT_EQ(str, obj.get());
	}
	{
		std::string str = "test";
		Path obj(str);

		EXPECT_EQ(str, obj.get());
	}
}

TEST(Path, PathType)
{
	Path obj("/absolute/path");
	EXPECT_EQ(true, obj.isAbsolute());

	obj.set("relative/path");
	EXPECT_EQ(true, obj.isRelative());

	obj.set("");
	EXPECT_EQ(false, obj.isRelative());
}
