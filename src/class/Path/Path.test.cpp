
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

	EXPECT_EQ(obj1.getPath(), obj3.getPath());
	obj2 = obj1;
	EXPECT_EQ(obj1.getPath(), obj2.getPath());
}

TEST(Path, Accessor)
{
	{
		std::string str = "";
		Path obj;

		EXPECT_EQ(str, obj.getPath());
		str = "test";
		obj.setPath(str);
		EXPECT_EQ(str, obj.getPath());
	}
	{
		std::string str = "test";
		Path obj(str);

		EXPECT_EQ(str, obj.getPath());
	}
}

TEST(Path, PathType)
{
	Path obj("/absolute/path");
	EXPECT_EQ(true, obj.isAbsolute());

	obj.setPath("relative/path");
	EXPECT_EQ(true, obj.isRelative());

	obj.setPath("");
	EXPECT_EQ(false, obj.isRelative());
}
