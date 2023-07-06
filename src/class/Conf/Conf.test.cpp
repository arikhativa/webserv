
#include <Conf/Conf.hpp>
#include <gtest/gtest.h>

TEST(Conf, CreateDestroy)
{
	Conf *obj = new Conf("path");
	delete obj;
}
