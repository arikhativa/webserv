
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <lexer/lexer.hpp>
#include <parser/parser.hpp>

TEST(parser, FullFile)
{
	std::fstream fs("res/tests/parser/parser_fullfile.conf");
	std::list< Token > list = lexer::tokenize(fs);

	ASSERT_EQ(true, parser::validate(list));
}

TEST(parser, BadFile0)
{
	std::fstream fs("res/tests/parser/parser_error0.conf");
	std::list< Token > list = lexer::tokenize(fs);

	ASSERT_EQ(false, parser::validate(list));
}

TEST(parser, BadFile1)
{
	std::fstream fs("res/tests/parser/parser_error1.conf");
	std::list< Token > list = lexer::tokenize(fs);

	ASSERT_EQ(false, parser::validate(list));
}

TEST(parser, BadFile2)
{
	std::fstream fs("res/tests/parser/parser_error2.conf");
	std::list< Token > list = lexer::tokenize(fs);

	ASSERT_EQ(false, parser::validate(list));
}

TEST(parser, BadFile3)
{
	std::fstream fs("res/tests/parser/parser_error3.conf");
	std::list< Token > list = lexer::tokenize(fs);

	ASSERT_EQ(false, parser::validate(list));
}

TEST(parser, BadFile4)
{
	std::fstream fs("res/tests/parser/parser_error4.conf");
	std::list< Token > list = lexer::tokenize(fs);

	ASSERT_EQ(false, parser::validate(list));
}

TEST(parser, BadFile5)
{
	std::fstream fs("res/tests/parser/parser_error5.conf");
	std::list< Token > list = lexer::tokenize(fs);

	ASSERT_EQ(false, parser::validate(list));
}

TEST(parser, CGIConf)
{
	std::fstream fs("res/tests/parser/parser_cgi.conf");
	std::list< Token > list = lexer::tokenize(fs);

	ASSERT_EQ(true, parser::validate(list));
}

TEST(parser, BadCGIConf)
{
	std::fstream fs("res/tests/parser/parser_bad_cgi.conf");
	std::list< Token > list = lexer::tokenize(fs);

	ASSERT_EQ(false, parser::validate(list));
}
