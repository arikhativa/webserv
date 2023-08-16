

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <BasicHTTPRequest/BasicHTTPRequest.hpp>
#include <builder/builder.hpp>
#include <lexer/lexer.hpp>
#include <matcher/matcher.hpp>
#include <parser/parser.hpp>

TEST(matcher, requestToServerWithHost)
{
	const char *file_name = "res/tests/matcher/simple.conf";

	std::fstream fs(file_name);
	std::list<Token> list = lexer::tokenize(fs);
	if (false == parser::validate(list))
		EXIT_FAILURE;

	const IConf *conf = builder::createConf(file_name, list);

	builder::validate(conf);

	BasicHTTPRequest req("GET / HTTP/1.1\r\nHost: pigafetta\r\n\r\n");
	req.parseRaw();

	Listen listen;

	const IServerConf *server = matcher::requestToServer(conf, &listen, req);

	EXPECT_EQ("pigafetta", server->getNames().front());
	delete conf;
}

TEST(matcher, requestToServerDefault)
{
	const char *file_name = "res/tests/matcher/simple.conf";

	std::fstream fs(file_name);
	std::list<Token> list = lexer::tokenize(fs);
	if (false == parser::validate(list))
		EXIT_FAILURE;

	const IConf *conf = builder::createConf(file_name, list);

	builder::validate(conf);

	BasicHTTPRequest req("GET / HTTP/1.1\r\nTest: yes\r\n\r\n");
	req.parseRaw();

	Listen listen;

	const IServerConf *server = matcher::requestToServer(conf, &listen, req);

	EXPECT_EQ("antonio", server->getNames().front());
	delete conf;
}

TEST(matcher, requestToServerDefaultWithHost)
{
	const char *file_name = "res/tests/matcher/simple.conf";

	std::fstream fs(file_name);
	std::list<Token> list = lexer::tokenize(fs);
	if (false == parser::validate(list))
		EXIT_FAILURE;

	const IConf *conf = builder::createConf(file_name, list);

	builder::validate(conf);

	BasicHTTPRequest req("GET / HTTP/1.1\r\nHost:\r\n\r\n");
	req.parseRaw();

	Listen listen;
	const IServerConf *server = matcher::requestToServer(conf, &listen, req);

	EXPECT_EQ("antonio", server->getNames().front());
	delete conf;
}

TEST(matcher, noMatchByListen)
{
	const char *file_name = "res/tests/matcher/simple2.conf";

	std::fstream fs(file_name);
	std::list<Token> list = lexer::tokenize(fs);
	if (false == parser::validate(list))
		EXIT_FAILURE;

	const IConf *conf = builder::createConf(file_name, list);

	builder::validate(conf);

	BasicHTTPRequest req("GET / HTTP/1.1\r\nHost: antonio\r\n\r\n");
	req.parseRaw();

	Listen listen;
	const IServerConf *server = matcher::requestToServer(conf, &listen, req);

	EXPECT_EQ(NULL, server);
	delete conf;
}

TEST(matcher, MatchByListenNoHost)
{
	const char *file_name = "res/tests/matcher/simple3.conf";

	std::fstream fs(file_name);
	std::list<Token> list = lexer::tokenize(fs);
	if (false == parser::validate(list))
		EXIT_FAILURE;

	const IConf *conf = builder::createConf(file_name, list);

	builder::validate(conf);

	BasicHTTPRequest req("GET / HTTP/1.1\r\nHost: antonio\r\n\r\n");
	req.parseRaw();

	Listen listen;
	const IServerConf *server = matcher::requestToServer(conf, &listen, req);

	EXPECT_EQ("pigafetta", server->getNames().front());
	delete conf;
}

TEST(matcher, requestToLocation)
{
	const char *file_name = "res/tests/matcher/simple4.conf";

	std::fstream fs(file_name);
	std::list<Token> list = lexer::tokenize(fs);
	if (false == parser::validate(list))
		EXIT_FAILURE;

	const IConf *conf = builder::createConf(file_name, list);

	builder::validate(conf);

	BasicHTTPRequest req("GET /2 HTTP/1.1\r\nHost: \r\n\r\n");
	req.parseRaw();

	Listen listen;
	const IServerConf *server = matcher::requestToServer(conf, &listen, req);
	const ILocation *l = matcher::requestToLocation(server, req);

	EXPECT_STREQ("/2", l->getPath().get().c_str());
	delete conf;
}
