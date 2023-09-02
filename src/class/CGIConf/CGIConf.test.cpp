
#include <CGIConf/CGIConf.hpp>
#include <gtest/gtest.h>

TEST(CGIConf, CreateDestroy)
{
	CGIConf *obj = new CGIConf();
	delete obj;
}

TEST(CGIConf, Accessor)
{
	CGIConf obj;

	obj.setExtension(".py");
	EXPECT_EQ(".py", obj.getExtension());

	obj.setPath("/path");
	EXPECT_EQ("/path", obj.getPath().get());
}

TEST(CGIConf, isSet)
{
	CGIConf obj;

	EXPECT_FALSE(obj.isSet());
	obj.setExtension(".py");
	obj.setPath("/path");
	EXPECT_TRUE(obj.isSet());
}
