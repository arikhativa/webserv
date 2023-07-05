
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <lexer/lexer.hpp>
#include <parser/parser.hpp>

TEST(parser, SimpleLine)
{
	std::fstream fs("res/tests/parser_simple.conf");
	std::list<Token> list = lexer::tokenize(fs);

	std::cout << std::endl;
	for (std::list<Token>::iterator it = list.begin(); it != list.end(); ++it)
		std::cout << *it << std::endl;
	std::cout << std::endl;
	ASSERT_EQ(true, parser::validate(list));
}
