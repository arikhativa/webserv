
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
	class Keyword
	{
	  private:
		Keyword(){};

	  public:
		static const std::string SERVER;
		static const std::string SERVER_NAME;
		static const std::string ROOT;
		static const std::string LISTEN;
		static const std::string INDEX;
		static const std::string ERROR_PAGE;
		static const std::string RETURN;
		static const std::string CLIENT_MAX_BODY_SIZE;
		static const std::string LOCATION;
		static const std::string ALLOW_METHODS;
		static const std::string AUTO_INDEX;
		static const std::string UPLOAD;
		static const std::string CGI;
	};
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
	static const std::map< std::string, bool > _keywords;
	static const std::map< type, std::string > _type_name;
	static const std::map< char, bool > _special_char;

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
