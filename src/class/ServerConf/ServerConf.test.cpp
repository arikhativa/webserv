
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
	obj.setIndexFiles(std::list<std::string>({"index.html", "index.php"}));
	obj.addErrorPage("404", "/404.html");
	obj.addErrorPage("505", "/505.html");
	obj.addListenByPort("1111");
	obj.addListenByIP("200.11.0.1");
	obj.addListen("80.80.80.80", "1234");
	{
		Location &l = obj.createGetLocation();
		l.setPath("/a");
		l.setDefaultSettingIfNeeded();
	}
	{
		Location &l = obj.createGetLocation();
		l.setPath("/b");
		l.setDefaultSettingIfNeeded();
	}

	EXPECT_EQ("name", obj.getName().front());
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

	std::list<const ILocation *> locations = obj.getLocations();
	EXPECT_EQ("/a", locations.front()->getPath().get());
	EXPECT_EQ(true, locations.front()->getAllowedMethods().isAllowed(IAllowedMethods::GET));

	EXPECT_EQ("/b", locations.back()->getPath().get());
}

TEST(ServerConf, Print)
{
	static const char *res =
		"{\"_name\": [\"name\"], \"_max_body_size\": 100, \"_return\": {\"_status\": 500, \"_path\": \"/500.html\"}, "
		"\"_root\": \"/root\", \"_index_files\": [\"index.html\", \"index.php\"], \"_error_pages\": [{\"_status\": "
		"404, \"_path\": \"/404.html\"}, {\"_status\": 505, \"_path\": \"/505.html\"}], \"_listen\": [{ \"_address\": "
		"\"0.0.0.0\", \"_port\": 1111 }, { \"_address\": \"200.11.0.1\", \"_port\": 80 }, { \"_address\": "
		"\"80.80.80.80\", \"_port\": 1234 }], \"_locations\": [{\"_path\": \"/a\", \"_auto_index\": false, "
		"\"_upload\": false, \"_max_body_size\": 0, \"_allowed_methods\": {\"post\": true, \"delete\": true}, "
		"\"_index_files\": [\"index.html\", \"index.php\"], \"_error_pages\": []}, {\"_path\": \"/b\", "
		"\"_auto_index\": true, \"_upload\": false, \"_max_body_size\": 0, \"_allowed_methods\": {\"get\": true, "
		"\"post\": true, \"delete\": true}, \"_index_files\": [], \"_error_pages\": []}]}";

	ServerConf obj;

	obj.addName("name");
	obj.setMaxBodySize("100");
	obj.setReturn("500", "/500.html");
	obj.setRoot("/root");
	obj.setIndexFiles(std::list<std::string>({"index.html", "index.php"}));
	obj.addErrorPage("404", "/404.html");
	obj.addErrorPage("505", "/505.html");
	obj.addListenByPort("1111");
	obj.addListenByIP("200.11.0.1");
	obj.addListen("80.80.80.80", "1234");
	{
		Location &l = obj.createGetLocation();
		l.setPath("/a");
		l.setIndexFiles(std::list<std::string>({"index.html", "index.php"}));
		l.setAllowedMethods(std::list<std::string>({"POST", "DELETE"}));
		l.setDefaultSettingIfNeeded();
	}
	{
		Location &l = obj.createGetLocation();
		l.setPath("/b");
		l.setAutoIndex("on");
		l.setDefaultSettingIfNeeded();
	}

	std::stringstream ss;
	ss << obj;
	EXPECT_EQ(res, ss.str());
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

	EXPECT_THROW(obj.setIndexFiles(std::list<std::string>{}), ServerConf::InvalidServerConf);
	obj.setIndexFiles(std::list<std::string>{"index.html"});
	EXPECT_THROW(obj.setIndexFiles(std::list<std::string>{"index.html"}), ServerConf::InvalidServerConf);
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
	EXPECT_EQ(ServerConf::DEFAULT_SERVER_NAME, obj.getName().front());
	EXPECT_EQ(ServerConf::DEFAULT_ROOT, obj.getRoot()->get());
	EXPECT_EQ(ServerConf::DEFAULT_HTML, obj.getIndexFiles().front());
	EXPECT_EQ(ServerConf::DEFAULT_HTM, obj.getIndexFiles().back());
}
