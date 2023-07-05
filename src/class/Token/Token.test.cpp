
#include <Token/Token.hpp>
#include <gtest/gtest.h>

TEST(Token, CreateDestroy)
{
	Token *obj = new Token();
	delete obj;
}

TEST(Token, Print)
{
	Token obj;
	std::stringstream buffer;
	std::streambuf *sbuf = std::cout.rdbuf();

	std::cout.rdbuf(buffer.rdbuf());
	std::cout << obj;
	std::cout.rdbuf(sbuf);
	ASSERT_EQ(buffer.str(), "Token[UNKNOWN]");
}
