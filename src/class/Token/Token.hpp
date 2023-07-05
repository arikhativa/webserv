
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

class Token
{
  public:
	enum type
	{
		UNKNOWN,
		KEYWORD,
		WORD,
		BLOCK_START,
		BLOCK_END,
		SEPARATOR,
		TILDE,
	};

	Token();
	explicit Token(const std::string &value);
	Token(Token const &src);
	~Token();

	Token &operator=(Token const &rhs);

	static std::string getTypeName(type t);

	type getType(void) const;
	std::string getValue(void) const;

  private:
	static std::map<std::string, bool> _keywords;
	static std::map<type, std::string> _type_name;

	type _type;
	std::string _value;

	static bool _isKeyword(const std::string &str);
	static type _initType(const std::string &str);
};

std::ostream &operator<<(std::ostream &o, Token const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* TOKEN_HPP */
