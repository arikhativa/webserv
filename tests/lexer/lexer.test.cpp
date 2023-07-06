
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <lexer/lexer.hpp>

TEST(lexer, SimpleLine)
{
	std::fstream fs("res/tests/lexer/lexer_simple.conf");
	std::list<Token> list = lexer::tokenize(fs);

	ASSERT_EQ(list.size(), 6);
	ASSERT_EQ(list.front().getType(), Token::KEYWORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::BLOCK_START);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::BLOCK_END);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::SEPARATOR);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::TILDE);
}

TEST(lexer, MultiLine)
{
	std::fstream fs("res/tests/lexer/lexer_simple_multi_line.conf");
	std::list<Token> list = lexer::tokenize(fs);

	ASSERT_EQ(list.size(), 12);
	ASSERT_EQ(list.front().getType(), Token::KEYWORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::BLOCK_START);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::KEYWORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::SEPARATOR);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::KEYWORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::SEPARATOR);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::BLOCK_END);
}

TEST(lexer, FullFile)
{
	std::fstream fs("res/tests/lexer/lexer_full_file.conf");
	std::list<Token> list = lexer::tokenize(fs);

	// server {
	ASSERT_EQ(list.size(), 59);
	ASSERT_EQ(list.front().getType(), Token::KEYWORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::BLOCK_START);
	list.pop_front();

	// 	server_name example.com www.example.com;
	ASSERT_EQ(list.front().getType(), Token::KEYWORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::SEPARATOR);
	list.pop_front();

	// root /var/www/example.com;
	ASSERT_EQ(list.front().getType(), Token::KEYWORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::SEPARATOR);
	list.pop_front();

	// listen 0.0.0.0:80;
	ASSERT_EQ(list.front().getType(), Token::KEYWORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::SEPARATOR);
	list.pop_front();

	// 	index index.html;
	ASSERT_EQ(list.front().getType(), Token::KEYWORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::SEPARATOR);
	list.pop_front();

	// error_page 404 /404.html;
	ASSERT_EQ(list.front().getType(), Token::KEYWORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::SEPARATOR);
	list.pop_front();

	// 	return 301 https://example.com/new-page;
	ASSERT_EQ(list.front().getType(), Token::KEYWORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::SEPARATOR);
	list.pop_front();

	// client_max_body_size 100M;
	ASSERT_EQ(list.front().getType(), Token::KEYWORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::SEPARATOR);
	list.pop_front();

	// 	location / {
	ASSERT_EQ(list.front().getType(), Token::KEYWORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::BLOCK_START);
	list.pop_front();

	// allow_methods GET POST;
	ASSERT_EQ(list.front().getType(), Token::KEYWORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::SEPARATOR);
	list.pop_front();

	// client_max_body_size 100M;
	ASSERT_EQ(list.front().getType(), Token::KEYWORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::SEPARATOR);
	list.pop_front();

	// root /var/www/example.com;
	ASSERT_EQ(list.front().getType(), Token::KEYWORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::SEPARATOR);
	list.pop_front();

	// index index.html;
	ASSERT_EQ(list.front().getType(), Token::KEYWORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::SEPARATOR);
	list.pop_front();

	// return 301 https://example.com/new-page;
	ASSERT_EQ(list.front().getType(), Token::KEYWORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::SEPARATOR);
	list.pop_front();

	// autoindex on;
	ASSERT_EQ(list.front().getType(), Token::KEYWORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::SEPARATOR);
	list.pop_front();

	// upload true;
	ASSERT_EQ(list.front().getType(), Token::KEYWORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::SEPARATOR);
	list.pop_front();

	// }
	ASSERT_EQ(list.front().getType(), Token::BLOCK_END);
	list.pop_front();

	// location ~ .php$ {
	ASSERT_EQ(list.front().getType(), Token::KEYWORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::TILDE);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::WORD);
	list.pop_front();
	ASSERT_EQ(list.front().getType(), Token::BLOCK_START);
	list.pop_front();

	// }
	ASSERT_EQ(list.front().getType(), Token::BLOCK_END);
	list.pop_front();

	// }
	ASSERT_EQ(list.front().getType(), Token::BLOCK_END);
	list.pop_front();

	ASSERT_EQ(list.size(), 0);
}
