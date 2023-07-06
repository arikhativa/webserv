
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
	// static
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

	static std::string getTypeName(type t);
	static bool isSpecialChar(char ch);
	static const char CHAR_SEPARATOR;
	static const char CHAR_TILDE;
	static const char CHAR_BLOCK_START;
	static const char CHAR_BLOCK_END;
	static const std::string STR_SEPARATOR;
	static const std::string STR_TILDE;
	static const std::string STR_BLOCK_START;
	static const std::string STR_BLOCK_END;
	static const std::string STR_GCI;

  private:
	static std::map<std::string, bool> _keywords;
	static std::map<type, std::string> _type_name;
	static std::map<char, bool> _special_char;

	static bool _isKeyword(const std::string &str);
	static type _initType(const std::string &str);

	// object
  public:
	Token();
	explicit Token(const std::string &value);
	Token(Token const &src);
	~Token();

	Token &operator=(Token const &rhs);

	type getType(void) const;
	std::string getValue(void) const;

  private:
	type _type;
	std::string _value;
};

std::ostream &operator<<(std::ostream &o, Token const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* TOKEN_HPP */
