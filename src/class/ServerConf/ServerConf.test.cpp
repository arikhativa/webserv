
#include <ServerConf/ServerConf.hpp>
#include <gtest/gtest.h>

TEST(ServerConf, CreateDestroy)
{
	ServerConf *obj = new ServerConf();
	delete obj;
}

TEST(ServerConf, getValue)
{
	int val(6);
	ServerConf i(val);
	EXPECT_EQ(val, i.getValue());
}

TEST(ServerConf, _setValue)
{
	ServerConf i;
	i._setValue(7);
	EXPECT_EQ(i.getValue(), 7);
}
