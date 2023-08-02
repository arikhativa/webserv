
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

TEST(Conf, Print)
{
	static const char *res =
		"{\"_file\": \"test\", \"_servers\": [{\"_name\": \"wordpress\", \"_max_body_size\": 100, \"_return\": "
		"{\"_status\": 500, \"_path\": \"/500.html\"}, \"_root\": \"/root\", \"_index_files\": [\"index.html\", "
		"\"index.php\"], \"_error_pages\": [{\"_status\": 404, \"_path\": \"/404.html\"}, {\"_status\": 505, "
		"\"_path\": \"/505.html\"}], \"_listen\": [{ \"_address\": \"80.80.80.80\", \"_port\": 1234 }], "
		"\"_locations\": [{\"_path\": \"/a\", \"_auto_index\": false, \"_upload\": false, \"_max_body_size\": 0, "
		"\"_allowed_methods\": {\"get\": true, \"post\": true, \"delete\": true}, \"_index_files\": [], "
		"\"_error_pages\": []}, {\"_path\": \"/b\", \"_auto_index\": false, \"_upload\": false, \"_max_body_size\": 0, "
		"\"_allowed_methods\": {\"get\": true, \"post\": true, \"delete\": true}, \"_index_files\": [], "
		"\"_error_pages\": []}]}, {\"_name\": \"google\", \"_max_body_size\": 20000, \"_return\": {\"_status\": 301, "
		"\"_path\": \"/301.html\"}, \"_root\": \"/var/www/html\", \"_index_files\": [\"index.py\", \"index.php\"], "
		"\"_error_pages\": [{\"_status\": 404, \"_path\": \"/404.html\"}, {\"_status\": 500, \"_path\": "
		"\"/500.html\"}], \"_listen\": [{ \"_address\": \"127.80.80.111\", \"_port\": 8080 }], \"_locations\": "
		"[{\"_path\": \"/location22\", \"_auto_index\": false, \"_upload\": false, \"_max_body_size\": 0, "
		"\"_allowed_methods\": {\"get\": true, \"post\": true, \"delete\": true}, \"_index_files\": [], "
		"\"_error_pages\": []}, {\"_path\": \"/location1000\", \"_auto_index\": false, \"_upload\": false, "
		"\"_max_body_size\": 0, \"_allowed_methods\": {\"get\": true, \"post\": true, \"delete\": true}, "
		"\"_index_files\": [], \"_error_pages\": []}]}]}";

	Conf obj("test");

	{
		ServerConf &server = obj.createGetServer();

		server.setName("wordpress");
		server.setMaxBodySize("100");
		server.setReturn("500", "/500.html");
		server.setRoot("/root");
		server.setIndexFiles(std::list<std::string>({"index.html", "index.php"}));
		server.addErrorPage("404", "/404.html");
		server.addErrorPage("505", "/505.html");
		server.addListen("80.80.80.80", "1234");
		{
			Location &l = server.createGetLocation();
			l.setPath("/a");
			l.setDefaultSettingIfNeeded();
		}
		{
			Location &l = server.createGetLocation();
			l.setPath("/b");
			l.setDefaultSettingIfNeeded();
		}
		server.setDefaultSettingIfNeeded();
	}
	{
		ServerConf &server = obj.createGetServer();

		server.setName("google");
		server.setMaxBodySize("20000");
		server.setReturn("301", "/301.html");
		server.setIndexFiles(std::list<std::string>({"index.py", "index.php"}));
		server.addErrorPage("404", "/404.html");
		server.addErrorPage("500", "/500.html");
		server.addListen("127.80.80.111", "8080");
		{
			Location &l = server.createGetLocation();
			l.setPath("/location22");
			l.setDefaultSettingIfNeeded();
		}
		{
			Location &l = server.createGetLocation();
			l.setPath("/location1000");
			l.setDefaultSettingIfNeeded();
		}
		server.setDefaultSettingIfNeeded();
	}

	std::stringstream ss;
	ss << obj;
	EXPECT_EQ(res, ss.str());
}

TEST(Conf, Empty)
{
	EXPECT_THROW(Conf obj(""), std::invalid_argument);
}

TEST(Conf, Default)
{
	static const char *res = "{\"_file\": \"file\", \"_servers\": [{\"_name\": \"\", \"_max_body_size\": 0, \"_root\": "
							 "\"/var/www/html\", \"_index_files\": [\"index.html\", \"index.htm\"], \"_error_pages\": "
							 "[], \"_listen\": [{ \"_address\": \"0.0.0.0\", \"_port\": 80 }], \"_locations\": []}]}";

	Conf obj("file");
	obj.addDefaultServerIfNeeded();

	std::stringstream ss;
	ss << obj;
	EXPECT_EQ(res, ss.str());
}
