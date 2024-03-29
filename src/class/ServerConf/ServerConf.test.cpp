
#include <ServerConf/ServerConf.hpp>
#include <gtest/gtest.h>

TEST(ServerConf, CreateDestroy)
{
	ServerConf *obj = new ServerConf();
	delete obj;
}

TEST(ServerConf, Accessor)
{
	ServerConf obj;

	obj.addName("name");
	obj.setMaxBodySize("100");
	obj.setReturn("500", "/500.html");
	obj.setRoot("/root");
	obj.setIndexFiles(std::list< std::string >({"index.html", "index.php"}));
	obj.addErrorPage("404", "/404.html");
	obj.addErrorPage("505", "/505.html");
	obj.addListenByPort("1111");
	obj.addListenByIP("200.11.0.1");
	obj.addListen("80.80.80.80", "1234");
	{
		Location &l = obj.createGetLocation();
		l.setPath("/a");
	}
	{
		Location &l = obj.createGetLocation();
		l.setPath("/b");
	}
	obj.setDefaultSettingIfNeeded();

	EXPECT_EQ("name", obj.getNames().front());
	EXPECT_EQ(100, obj.getMaxBodySize());
	EXPECT_EQ(500, obj.getReturn()->getStatus().get());
	EXPECT_EQ("/500.html", obj.getReturn()->getPath().get());
	EXPECT_EQ("/root", obj.getRoot()->get());
	EXPECT_EQ("index.html", obj.getIndexFiles().front());
	EXPECT_EQ("index.php", obj.getIndexFiles().back());
	EXPECT_EQ(404, obj.getErrorPages().front()->getStatus().get());
	EXPECT_EQ("/404.html", obj.getErrorPages().front()->getPath().get());
	EXPECT_EQ(505, obj.getErrorPages().back()->getStatus().get());
	EXPECT_EQ("/505.html", obj.getErrorPages().back()->getPath().get());
	EXPECT_EQ(1111, obj.getListen().front()->getPort().get());

	std::list< const ILocation * > locations = obj.getLocations();
	EXPECT_EQ("/a", locations.front()->getPath().get());
	EXPECT_EQ(true, locations.front()->getAllowedMethods().isAllowed(IAllowedMethods::GET));
	locations.pop_front();
	EXPECT_EQ("/b", locations.front()->getPath().get());
	locations.pop_front();
	EXPECT_EQ("/", locations.front()->getPath().get());
}

TEST(ServerConf, setMaxBodySize)
{
	ServerConf obj;

	EXPECT_THROW(obj.setMaxBodySize(""), std::invalid_argument);
	obj.setMaxBodySize("2");
	EXPECT_THROW(obj.setMaxBodySize("2"), ServerConf::InvalidServerConf);
}

TEST(ServerConf, setReturn)
{
	ServerConf obj;

	obj.setReturn("200", "f.html");
	EXPECT_THROW(obj.setReturn("200", "f.html"), ServerConf::InvalidServerConf);
}

TEST(ServerConf, setRoot)
{
	ServerConf obj;

	EXPECT_THROW(obj.setRoot(""), ServerConf::InvalidServerConf);
	obj.setRoot("/");
	EXPECT_THROW(obj.setRoot("/"), ServerConf::InvalidServerConf);
}

TEST(ServerConf, setIndexFiles)
{
	ServerConf obj;

	EXPECT_THROW(obj.setIndexFiles(std::list< std::string >{}), ServerConf::InvalidServerConf);
	obj.setIndexFiles(std::list< std::string >{"index.html"});
	EXPECT_THROW(obj.setIndexFiles(std::list< std::string >{"index.html"}), ServerConf::InvalidServerConf);
}

TEST(ServerConf, addErrorPage)
{
	ServerConf obj;

	obj.addErrorPage("200", "f.html");
	EXPECT_THROW(obj.addErrorPage("200", "f.html"), ServerConf::InvalidServerConf);
}

TEST(ServerConf, addListen)
{
	ServerConf obj;

	obj.addListen("127.0.0.1", "8080");
	EXPECT_THROW(obj.addListen("127.0.0.1", "8080"), ServerConf::InvalidServerConf);
}

TEST(ServerConf, setDefaultSettingIfNeeded)
{
	ServerConf obj;

	obj.setDefaultSettingIfNeeded();
	EXPECT_EQ(ServerConf::DEFAULT_SERVER_NAME, obj.getNames().front());
	EXPECT_EQ(ServerConf::DEFAULT_ROOT, obj.getRoot()->get());
	EXPECT_EQ(ServerConf::DEFAULT_HTML, obj.getIndexFiles().front());
	EXPECT_EQ(ServerConf::DEFAULT_HTM, obj.getIndexFiles().back());

	std::list< const ILocation * > locations = obj.getLocations();
	EXPECT_EQ("/", locations.front()->getPath().get());
	EXPECT_EQ(ServerConf::DEFAULT_ROOT, locations.front()->getRoot()->get());
}

TEST(ServerConf, _inheritFromServer)
{
	ServerConf obj;

	obj.setRoot("/root");
	obj.setIndexFiles(std::list< std::string >({"index.html", "index.php"}));
	{
		Location &l = obj.createGetLocation();
		l.setPath("/b");
	}

	obj.setDefaultSettingIfNeeded();

	std::list< const ILocation * > locations = obj.getLocations();
	EXPECT_EQ("/b", locations.front()->getPath().get());
	EXPECT_EQ("/root", locations.front()->getRoot()->get());
	EXPECT_EQ("index.html", locations.front()->getIndexFiles().front());

	EXPECT_EQ("/", locations.back()->getPath().get());
	EXPECT_EQ("/root", locations.back()->getRoot()->get());
	EXPECT_EQ("index.php", locations.back()->getIndexFiles().back());
}
