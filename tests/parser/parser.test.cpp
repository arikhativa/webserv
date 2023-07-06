
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <lexer/lexer.hpp>
#include <parser/parser.hpp>

TEST(parser, FullFile)
{
	std::fstream fs("res/tests/parser/parser_fullfile.conf");
	std::list<Token> list = lexer::tokenize(fs);

	ASSERT_EQ(true, parser::validate(list));
}
