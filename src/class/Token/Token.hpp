
#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>
#include <map>
#include <string>

#include <Token/Token.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

typedef enum e_token_type
{
	UNKNOWN,
	KEYWORD,
	WORD,
	BLOCK_START,
	BLOCK_END,
	SEPARATOR,
	TILDE,
} t_token_type;

class Token
{
  public:
	Token();
	explicit Token(const std::string &value);
	Token(Token const &src);
	~Token();

	Token &operator=(Token const &rhs);

	static std::string Token::getTypeName(t_token_type t);

	t_token_type Token::getType(void) const;
	std::string Token::getValue(void) const;

  private:
	static std::map<std::string, bool> _keywords;
	static std::map<t_token_type, std::string> _type_name;

	t_token_type _type;
	std::string _value;

	static t_token_type _initType(const std::string &str);
};

std::ostream &operator<<(std::ostream &o, Token const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* TOKEN_HPP */
