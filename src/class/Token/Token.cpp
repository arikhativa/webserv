
#include <Token/Token.hpp>

static std::map<Token::type, std::string> initTokenName(void)
{
	std::map<Token::type, std::string> ret;

	ret[Token::UNKNOWN] = "UNKNOWN";
	ret[Token::KEYWORD] = "KEYWORD";
	ret[Token::WORD] = "WORD";
	ret[Token::BLOCK_START] = "BLOCK_START";
	ret[Token::BLOCK_END] = "BLOCK_END";
	ret[Token::SEPARATOR] = "SEPARATOR";
	ret[Token::TILDE] = "TILDE";

	return ret;
}

static std::map<std::string, bool> initKeywords(void)
{
	std::map<std::string, bool> ret;

	ret["server"] = true;
	ret["server_name"] = true;
	ret["root"] = true;
	ret["listen"] = true;
	ret["index"] = true;
	ret["error_page"] = true;
	ret["return"] = true;
	ret["client_max_body_size"] = true;
	ret["location"] = true;
	ret["allow_methods"] = true;
	ret["autoindex"] = true;
	ret["upload"] = true;

	return ret;
}

static std::map<char, bool> initSpecialChar(void)
{
	std::map<char, bool> ret;

	ret['{'] = true;
	ret['}'] = true;
	ret['~'] = true;
	ret[';'] = true;

	return ret;
}

std::map<std::string, bool> Token::_keywords(initKeywords());
std::map<Token::type, std::string> Token::_type_name(initTokenName());
std::map<char, bool> Token::_special_char(initSpecialChar());

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Token::Token()
	: _type(UNKNOWN)
	, _value("")
{
}

// TODO think about exceptions
Token::Token(const std::string &value)
	: _type(Token::_initType(value))
	, _value(value)
{
	if (_type == UNKNOWN)
		throw std::invalid_argument("Unknown token type");
}

Token::Token(const Token &src)
	: _type(src.getType())
	, _value(src.getValue())
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Token::~Token()
{
	_type = UNKNOWN;
	_value = "";
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Token &Token::operator=(Token const &rhs)
{
	if (this != &rhs)
	{
		this->_type = rhs.getType();
		this->_value = rhs.getValue();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, Token const &i)
{
	o << "Token[" << Token::getTypeName(i.getType()) << "]";
	return o;
}

/*
** ------------------------------ STATIC METHODS -------------------------------
*/

bool Token::isSpecialChar(char ch)
{
	return (Token::_special_char[ch]);
}

bool Token::_isKeyword(const std::string &str)
{
	return Token::_keywords[str];
}

std::string Token::getTypeName(Token::type t)
{
	return _type_name[t];
}

Token::type Token::_initType(const std::string &str)
{
	if (_isKeyword(str))
		return KEYWORD;
	else if (str == "{")
		return BLOCK_START;
	else if (str == "}")
		return BLOCK_END;
	else if (str == ";")
		return SEPARATOR;
	else if (str == "~")
		return TILDE;
	else if (!str.empty())
		return WORD;
	return UNKNOWN;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

Token::type Token::getType(void) const
{
	return this->_type;
}

std::string Token::getValue(void) const
{
	return this->_value;
}

/* ************************************************************************** */
