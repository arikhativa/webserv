
#include <Token/Token.hpp>

std::map<std::string, bool> Token::_keywords = {
	{"server", true},	{"server_name", true},	 {"root", true},	  {"listen", true},
	{"index", true},	{"error_page", true},	 {"return", true},	  {"client_max_body_size", true},
	{"location", true}, {"allow_methods", true}, {"autoindex", true}, {"upload", true},
};

std::map<t_token_type, std::string> Token::_type_name = {
	{UNKNOWN, "UNKNOWN"},	  {KEYWORD, "KEYWORD"},		{WORD, "WORD"},	  {BLOCK_START, "BLOCK_START"},
	{BLOCK_END, "BLOCK_END"}, {SEPARATOR, "SEPARATOR"}, {TILDE, "TILDE"},
};

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
	: _type(_initType(value))
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

std::string Token::getTypeName(t_token_type t)
{
	return _type_name[t];
}

t_token_type Token::_initType(const std::string &str)
{
	if (_keywords[str])
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
