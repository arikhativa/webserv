
#include <Token/Token.hpp>
#include <gtest/gtest.h>

TEST(Token, CreateDestroy)
{
	Token *obj = new Token();
	delete obj;
}

TEST(Token, Print)
{
	{
		Token obj;
		std::stringstream buffer;
		std::streambuf *sbuf = std::cout.rdbuf();

		std::cout.rdbuf(buffer.rdbuf());
		std::cout << obj;
		std::cout.rdbuf(sbuf);
		ASSERT_EQ(buffer.str(), "Token[UNKNOWN]");
	}
	{
		Token obj(Token::Keyword::SERVER);
		std::stringstream buffer;
		std::streambuf *sbuf = std::cout.rdbuf();

		std::cout.rdbuf(buffer.rdbuf());
		std::cout << obj;
		std::cout.rdbuf(sbuf);
		ASSERT_EQ(buffer.str(), "Token[KEYWORD]");
	}
}

TEST(Token, Type)
{
	{
		Token obj;
		ASSERT_EQ(obj.getType(), Token::UNKNOWN);
	}
	{
		Token obj(Token::Keyword::SERVER);
		ASSERT_EQ(obj.getType(), Token::KEYWORD);
	}
	{
		Token obj("0.0.0.0::8080");
		ASSERT_EQ(obj.getType(), Token::WORD);
	}
	{
		Token obj("{");
		ASSERT_EQ(obj.getType(), Token::BLOCK_START);
	}
	{
		Token obj("}");
		ASSERT_EQ(obj.getType(), Token::BLOCK_END);
	}
	{
		Token obj(";");
		ASSERT_EQ(obj.getType(), Token::SEPARATOR);
	}
	{
		Token obj("~");
		ASSERT_EQ(obj.getType(), Token::TILDE);
	}
}
