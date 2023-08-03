
#include <iostream>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <IConf/IConf.hpp>
#include <ILocation/ILocation.hpp>
#include <IServerConf/IServerConf.hpp>
#include <builder/builder.hpp>
#include <lexer/lexer.hpp>
#include <parser/parser.hpp>

TEST(builder, SimpleFile)
{
	std::fstream fs("res/tests/builder/simple.conf");
	std::list<Token> list = lexer::tokenize(fs);

	const IConf *conf = builder::createConf("res/tests/builder/simple.conf", list);
	const IServerConf *server = conf->getServers().front();
	std::list<const IListen *> listen = server->getListen();
	std::list<const IListen *>::iterator it = listen.begin();

	EXPECT_EQ(1, conf->getServers().size());
	EXPECT_EQ("", server->getName());

	EXPECT_EQ("0.0.0.0", (*it)->getAddress().getAddress());
	EXPECT_EQ(88, (*it)->getPort().get());

	++it;
	EXPECT_EQ("201.0.0.1", (*it)->getAddress().getAddress());
	EXPECT_EQ(80, (*it)->getPort().get());

	++it;
	EXPECT_EQ("101.0.0.2", (*it)->getAddress().getAddress());
	EXPECT_EQ(666, (*it)->getPort().get());

	delete conf;
}

TEST(builder, FullFile)
{
	std::fstream fs("res/tests/builder/full.conf");
	std::list<Token> list = lexer::tokenize(fs);
	if (false == parser::validate(list))
	{
		EXIT_FAILURE;
	}

	const IConf *conf = builder::createConf("res/tests/builder/full.conf", list);
	std::list<const IServerConf *> servers = conf->getServers();
	std::list<const IServerConf *>::iterator s_it = servers.begin();

	// server #0
	EXPECT_EQ("", (*s_it)->getName());
	EXPECT_EQ(0, (*s_it)->getMaxBodySize());
	{
		std::list<std::string> l = (*s_it)->getIndexFiles();
		std::list<std::string>::iterator it = l.begin();
		EXPECT_EQ("index.html", *it);
		++it;
		EXPECT_EQ("index.htm", *it);
	}
	{
		std::list<const IListen *> l = (*s_it)->getListen();
		std::list<const IListen *>::iterator it = l.begin();
		EXPECT_EQ("0.0.0.0", (*it)->getAddress().getAddress());
		EXPECT_EQ(80, (*it)->getPort().get());
	}

	// server #1
	++s_it;
	EXPECT_EQ("pigafetta", (*s_it)->getName());
	EXPECT_EQ(20, (*s_it)->getMaxBodySize());
	EXPECT_EQ(200, (*s_it)->getReturn()->getStatus().get());
	EXPECT_EQ("/200.html", (*s_it)->getReturn()->getPath().get());
	EXPECT_EQ("/asd", (*s_it)->getRoot()->get());
	{
		std::list<std::string> l = (*s_it)->getIndexFiles();
		std::list<std::string>::iterator it = l.begin();
		EXPECT_EQ("1.htm", *it);
		++it;
		EXPECT_EQ("2.htm", *it);
		++it;
		EXPECT_EQ("3.htm", *it);
	}
	{
		std::list<const IListen *> l = (*s_it)->getListen();
		std::list<const IListen *>::iterator it = l.begin();
		EXPECT_EQ("127.0.0.2", (*it)->getAddress().getAddress());
		EXPECT_EQ(6660, (*it)->getPort().get());
	}
	{
		std::list<const ILocation *> l = (*s_it)->getLocations();
		std::list<const ILocation *>::iterator it = l.begin();

		EXPECT_EQ("/DEL", (*it)->getPath().get());
		EXPECT_EQ(true, (*it)->getAllowedMethods().isAllowed(IAllowedMethods::DELETE));
		EXPECT_EQ(false, (*it)->getAllowedMethods().isAllowed(IAllowedMethods::POST));
		EXPECT_EQ(false, (*it)->getAllowedMethods().isAllowed(IAllowedMethods::GET));
		EXPECT_EQ(0, (*it)->getMaxBodySize());
		EXPECT_EQ(false, (*it)->isAutoIndexOn());
		EXPECT_EQ(false, (*it)->canUpload());
	}

	// server #2
	++s_it;
	EXPECT_EQ("yoda.com", (*s_it)->getName());
	EXPECT_EQ(100, (*s_it)->getMaxBodySize());
	EXPECT_EQ(500, (*s_it)->getReturn()->getStatus().get());
	EXPECT_EQ("/500.html", (*s_it)->getReturn()->getPath().get());
	EXPECT_EQ("/var/www/example.com", (*s_it)->getRoot()->get());
	{
		std::list<std::string> l = (*s_it)->getIndexFiles();
		std::list<std::string>::iterator it = l.begin();
		EXPECT_EQ("1.htm", *it);
		++it;
		EXPECT_EQ("2.htm", *it);
		++it;
		EXPECT_EQ("3.htm", *it);
	}
	{
		std::list<const IListen *> l = (*s_it)->getListen();
		std::list<const IListen *>::iterator it = l.begin();

		EXPECT_EQ("1.1.2.2", (*it)->getAddress().getAddress());
		EXPECT_EQ(89, (*it)->getPort().get());

		++it;
		EXPECT_EQ("8.8.8.8", (*it)->getAddress().getAddress());
		EXPECT_EQ(88, (*it)->getPort().get());
	}
	{
		std::list<const ILocation *> l = (*s_it)->getLocations();
		std::list<const ILocation *>::iterator it = l.begin();

		EXPECT_EQ("/loc1", (*it)->getPath().get());
		EXPECT_EQ("/var/www/example1.com", (*it)->getRoot()->get());
		EXPECT_EQ(HTTPStatusCode::SEE_OTHER, (*it)->getReturn()->getStatus().get());
		EXPECT_EQ("/303.html", (*it)->getReturn()->getPath().get());
		EXPECT_EQ(false, (*it)->getAllowedMethods().isAllowed(IAllowedMethods::DELETE));
		EXPECT_EQ(true, (*it)->getAllowedMethods().isAllowed(IAllowedMethods::POST));
		EXPECT_EQ(false, (*it)->getAllowedMethods().isAllowed(IAllowedMethods::GET));
		EXPECT_EQ(0, (*it)->getMaxBodySize());
		EXPECT_EQ(true, (*it)->isAutoIndexOn());
		EXPECT_EQ(true, (*it)->canUpload());
		{
			std::list<std::string> loc_list = (*it)->getIndexFiles();
			std::list<std::string>::iterator l_it = loc_list.begin();
			EXPECT_EQ("1.htm", *l_it);
			++l_it;
			EXPECT_EQ("2.htm", *l_it);
			++l_it;
			EXPECT_EQ("3.htm", *l_it);
		}

		++it;
		EXPECT_EQ("/loc2", (*it)->getPath().get());
		EXPECT_EQ("/var/www/example2.com", (*it)->getRoot()->get());
		EXPECT_EQ(HTTPStatusCode::BAD_REQUEST, (*it)->getReturn()->getStatus().get());
		EXPECT_EQ("/400.html", (*it)->getReturn()->getPath().get());
		EXPECT_EQ(false, (*it)->getAllowedMethods().isAllowed(IAllowedMethods::DELETE));
		EXPECT_EQ(true, (*it)->getAllowedMethods().isAllowed(IAllowedMethods::POST));
		EXPECT_EQ(true, (*it)->getAllowedMethods().isAllowed(IAllowedMethods::GET));
		EXPECT_EQ(555, (*it)->getMaxBodySize());
		EXPECT_EQ(false, (*it)->isAutoIndexOn());
		EXPECT_EQ(true, (*it)->canUpload());
	}

	delete conf;
}
