
#include <Listen/Listen.hpp>
#include <gtest/gtest.h>

TEST(Listen, CreateDestroy)
{
	Listen *obj = new Listen();
	delete obj;
}

TEST(Listen, Accessor)
{
	Listen obj;

	EXPECT_EQ(Listen::_defaultIP, obj.getAddress().getAddress());
	EXPECT_EQ(Listen::_defaultPort, obj.getPort().get());
	obj.setAddress("127.0.0.1");
	obj.setPort("443");
	EXPECT_EQ("127.0.0.1", obj.getAddress().getAddress());
	EXPECT_EQ(443, obj.getPort().get());
}

TEST(Listen, Print)
{
	Listen obj;

	obj.setAddress("127.0.0.1");
	std::stringstream ss;
	ss << obj;
	EXPECT_EQ("{ \"_address\": \"127.0.0.1\", \"_port\": 80 }", ss.str());
}
