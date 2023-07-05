
#include <ConfFile/ConfFile.hpp>
#include <gtest/gtest.h>

TEST(ConfFile, CreateDestroy)
{
	ConfFile *obj = new ConfFile("res/basic.conf");
	delete obj;
}
