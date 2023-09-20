
#include <Location/Location.hpp>
#include <gtest/gtest.h>

TEST(Location, CreateDestroy)
{
	Location *obj = new Location();
	delete obj;
}

TEST(Location, Accessor)
{
	Location *ptr = new Location();

	ptr->setAutoIndex("on");
	ptr->setUpload("on");
	ptr->setMaxBodySize("100");
	ptr->setPath("/");
	ptr->setIndexFiles(std::list< std::string >({"index.html", "index.php"}));
	ptr->setAllowedMethods(std::list< std::string >({"GET", "DELETE"}));
	ptr->setReturn("200", "/index.html");
	ptr->addErrorPage("404", "/404.html");
	ptr->addErrorPage("505", "/505.html");
	ptr->setRoot("/root");

	EXPECT_EQ(true, ptr->isAutoIndexOn());
	EXPECT_EQ(true, ptr->canUpload());
	EXPECT_EQ(100, ptr->getMaxBodySize());
	EXPECT_EQ("/", ptr->getPath().get());
	EXPECT_EQ("index.html", ptr->getIndexFiles().front());
	EXPECT_EQ("index.php", ptr->getIndexFiles().back());
	EXPECT_EQ(true, ptr->getAllowedMethods().isAllowed(IAllowedMethods::GET));
	EXPECT_EQ(false, ptr->getAllowedMethods().isAllowed(IAllowedMethods::POST));
	EXPECT_EQ(true, ptr->getAllowedMethods().isAllowed(IAllowedMethods::DELETE));
	EXPECT_EQ(200, ptr->getReturn()->getStatus().get());
	EXPECT_EQ("/index.html", ptr->getReturn()->getPath().get());
	EXPECT_EQ(404, ptr->getErrorPages().front()->getStatus().get());
	EXPECT_EQ("/404.html", ptr->getErrorPages().front()->getPath().get());
	EXPECT_EQ(505, ptr->getErrorPages().back()->getStatus().get());
	EXPECT_EQ("/505.html", ptr->getErrorPages().back()->getPath().get());
	EXPECT_EQ("/root", ptr->getRoot()->get());

	delete ptr;
}

TEST(Location, Print)
{
	static const char *res =
		"{\"_path\": \"/path\", \"_auto_index\": true, \"_upload\": true, \"_max_body_size\": 100, "
		"\"_allowed_methods\": {\"get\": true, \"post\": true, \"delete\": true}, \"_return\": {\"_status\": 200, "
		"\"_path\": \"/index.html\"}, \"_index_files\": [\"index.html\", \"index.php\"], \"_error_pages\": "
		"[{\"_status\": 404, \"_path\": \"/404.html\"}], \"_root\": \"/root\"}";

	Location obj;

	obj.setPath("/path");
	obj.setAutoIndex("on");
	obj.setUpload("on");
	obj.setMaxBodySize("100");
	obj.setIndexFiles(std::list< std::string >({"index.html", "index.php"}));
	obj.setAllowedMethods(std::list< std::string >({"GET", "POST", "DELETE"}));
	obj.setReturn("200", "/index.html");
	obj.addErrorPage("404", "/404.html");
	obj.setRoot("/root");

	std::stringstream ss;
	ss << obj;
	EXPECT_EQ(res, ss.str());
}

TEST(Location, ExceptionAutoIndex)
{
	Location obj;

	EXPECT_THROW(obj.setAutoIndex("1"), std::invalid_argument);
	obj.setAutoIndex("on");
	EXPECT_THROW(obj.setAutoIndex("on"), Location::InvalidLocationException);
}

TEST(Location, ExceptionUpload)
{
	Location obj;

	EXPECT_THROW(obj.setUpload("1"), std::invalid_argument);
	obj.setUpload("on");
	EXPECT_THROW(obj.setUpload("on"), Location::InvalidLocationException);
}

TEST(Location, ExceptionMaxBodySize)
{
	Location obj;

	EXPECT_THROW(obj.setMaxBodySize("-1"), std::invalid_argument);
	obj.setMaxBodySize("100");
	EXPECT_THROW(obj.setMaxBodySize("0"), Location::InvalidLocationException);
}

TEST(Location, ExceptionAllowedMethods)
{
	Location obj;

	EXPECT_THROW(obj.setAllowedMethods(std::list< std::string >()), Location::InvalidLocationException);
	EXPECT_THROW(obj.setAllowedMethods(std::list< std::string >({"asd"})), AllowedMethods::InvalidMethodException);
	obj.setAllowedMethods(std::list< std::string >({"POST"}));
	EXPECT_THROW(obj.setAllowedMethods(std::list< std::string >({"POST"})), Location::InvalidLocationException);
}

TEST(Location, ExceptionsetReturn)
{
	Location obj;

	EXPECT_THROW(obj.setReturn("-2", "./html.html"), HTTPStatusCode::InvalidStatusCodeException);
	EXPECT_THROW(obj.setReturn("200", ""), BasePairCodePath::InvalidPathException);
	obj.setReturn("301", "./ret.html");
	EXPECT_THROW(obj.setReturn("301", "./ret.html"), Location::InvalidLocationException);
}

TEST(Location, ExceptionIndexFiles)
{
	Location obj;

	EXPECT_THROW(obj.setIndexFiles(std::list< std::string >()), Location::InvalidLocationException);
	obj.setIndexFiles(std::list< std::string >({"index.html"}));
	EXPECT_THROW(obj.setIndexFiles(std::list< std::string >({"index.html"})), Location::InvalidLocationException);
}

TEST(Location, ExceptionErrorPage)
{
	Location obj;

	EXPECT_THROW(obj.addErrorPage("-2", "./html.html"), HTTPStatusCode::InvalidStatusCodeException);
	EXPECT_THROW(obj.addErrorPage("", "./html.html"), HTTPStatusCode::InvalidStatusCodeException);
	EXPECT_THROW(obj.addErrorPage("200", ""), BasePairCodePath::InvalidPathException);
	obj.addErrorPage("200", "./file.html");
	EXPECT_THROW(obj.addErrorPage("200", "./file.html"), Location::InvalidLocationException);
}

TEST(Location, ExceptionRoot)
{
	Location obj;

	EXPECT_THROW(obj.setRoot(""), Location::InvalidLocationException);
	obj.setRoot("/root");
	EXPECT_THROW(obj.setRoot("/root"), Location::InvalidLocationException);
}

TEST(Location, getReturn)
{
	Location obj;

	EXPECT_EQ(NULL, obj.getReturn());
}

TEST(Location, setDefaultSettingIfNeeded)
{
	Location obj;

	obj.setPath("/");
	obj.setDefaultSettingIfNeeded();

	EXPECT_EQ(false, obj.isAutoIndexOn());
	EXPECT_EQ(false, obj.canUpload());
	EXPECT_EQ(0, obj.getMaxBodySize());
	EXPECT_EQ("/", obj.getPath().get());
	EXPECT_EQ(0, obj.getIndexFiles().size());
	EXPECT_EQ(true, obj.getAllowedMethods().isAllowed(IAllowedMethods::GET));
	EXPECT_EQ(true, obj.getAllowedMethods().isAllowed(IAllowedMethods::POST));
	EXPECT_EQ(true, obj.getAllowedMethods().isAllowed(IAllowedMethods::DELETE));
	EXPECT_EQ(NULL, obj.getReturn());
	EXPECT_EQ(0, obj.getErrorPages().size());
}

TEST(Location, CGIConf)
{
	Location obj;

	EXPECT_FALSE(obj.getCGIConf().isSet());

	obj.setCGI(".php", "/usr/bin/php-cgi");

	EXPECT_EQ(".php", obj.getCGIConf().getExtension());
	EXPECT_EQ("/usr/bin/php-cgi", obj.getCGIConf().getPath().get());
}

TEST(Location, ExceptionCGIConf)
{
	Location obj;

	EXPECT_FALSE(obj.getCGIConf().isSet());

	EXPECT_THROW(obj.setCGI(".invalid", "/usr/bin/php-cgi"), CGIConf::InvalidExtension);
	obj.setCGI(".php", "/usr/bin/php-cgi");
	EXPECT_THROW(obj.setCGI(".php", "/usr/bin/php-cgi"), Location::InvalidLocationException);
}

TEST(Location, getErrorPageSet)
{
	Location obj;

	obj.setRoot("/new");
	obj.addErrorPage("100", "/100.html");
	obj.addErrorPage("404", "/new.html");
	obj.setDefaultSettingIfNeeded();
	EXPECT_EQ(obj.getErrorPageSet().getPage(HTTPStatusCode::Code::CONTINUE), "/new/100.html");
	EXPECT_EQ(obj.getErrorPageSet().getPage(HTTPStatusCode::Code::NOT_FOUND), "/new/new.html");
	EXPECT_EQ(obj.getErrorPageSet().getPage(HTTPStatusCode::Code::METHOD_NOT_ALLOWED),
			  "res/default_error_pages/405.html");
}
