
#include <Token/Token.hpp>

std::map<std::string, bool> Token::_keywords;
std::map<t_token_type, std::string> Token::_type_name;

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
void Token::_initTokenName(void)
{
	Token::_type_name[UNKNOWN] = "UNKNOWN";
	Token::_type_name[KEYWORD] = "KEYWORD";
	Token::_type_name[WORD] = "WORD";
	Token::_type_name[BLOCK_START] = "BLOCK_START";
	Token::_type_name[BLOCK_END] = "BLOCK_END";
	Token::_type_name[SEPARATOR] = "SEPARATOR";
	Token::_type_name[TILDE] = "TILDE";
}

void Token::_initKeywords(void)
{
	Token::_keywords["server"] = true;
	Token::_keywords["server_name"] = true;
	Token::_keywords["root"] = true;
	Token::_keywords["listen"] = true;
	Token::_keywords["index"] = true;
	Token::_keywords["error_page"] = true;
	Token::_keywords["return"] = true;
	Token::_keywords["client_max_body_size"] = true;
	Token::_keywords["location"] = true;
	Token::_keywords["allow_methods"] = true;
	Token::_keywords["autoindex"] = true;
	Token::_keywords["upload"] = true;
}

bool Token::_isKeyword(const std::string &str)
{
	if (Token::_keywords.empty())
		Token::_initKeywords();
	return Token::_keywords[str];
}

std::string Token::getTypeName(t_token_type t)
{
	if (Token::_type_name.empty())
		Token::_initTokenName();
	return _type_name[t];
}

t_token_type Token::_initType(const std::string &str)
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

t_token_type Token::getType(void) const
{
	return this->_type;
}

std::string Token::getValue(void) const
{
	return this->_value;
}

/* ************************************************************************** */
