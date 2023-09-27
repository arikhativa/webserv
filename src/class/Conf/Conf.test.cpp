
#include <Conf/Conf.hpp>
#include <gtest/gtest.h>

TEST(Conf, CreateDestroy)
{
	Conf *obj = new Conf("test");
	delete obj;
}

TEST(Conf, Accessor)
{
	Conf obj("test");

	{
		ServerConf &server = obj.createGetServer();
		server.setDefaultSettingIfNeeded();
	}
	{
		ServerConf &server = obj.createGetServer();
		server.setDefaultSettingIfNeeded();
	}

	EXPECT_EQ("test", obj.getFileName());
	EXPECT_EQ(2, obj.getServers().size());
}

TEST(Conf, Empty)
{
	EXPECT_THROW(Conf obj(""), std::invalid_argument);
}

TEST(Conf, Default)
{

	Conf obj("file");
	obj.addDefaultServerIfNeeded();

	std::list< const IServerConf * > server = obj.getServers();
	const IServerConf *s = server.front();

	EXPECT_EQ("", s->getNames().front());
	EXPECT_EQ(0, s->getMaxBodySize());
	EXPECT_EQ("/var/www/html", s->getRoot()->get());
	{
		std::list< const IListen * > l = s->getListen();
		std::list< const IListen * >::iterator it = l.begin();

		EXPECT_EQ("0.0.0.0", (*it)->getAddress().get());
		EXPECT_EQ(80, (*it)->getPort().get());
	}
	{
		const std::list< std::string > &l = s->getIndexFiles();

		EXPECT_EQ("index.html", l.front());
		EXPECT_EQ("index.htm", l.back());
	}
}
