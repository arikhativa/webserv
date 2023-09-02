
#include <parser/parser.hpp>

static std::map<std::string, bool> initServerValidKeywords(void)
{
	std::map<std::string, bool> map;

	map[Token::Keyword::SERVER_NAME] = true;
	map[Token::Keyword::ROOT] = true;
	map[Token::Keyword::LISTEN] = true;
	map[Token::Keyword::INDEX] = true;
	map[Token::Keyword::ERROR_PAGE] = true;
	map[Token::Keyword::RETURN] = true;
	map[Token::Keyword::CLIENT_MAX_BODY_SIZE] = true;
	map[Token::Keyword::LOCATION] = true;

	return map;
}

static std::map<std::string, bool> initLocationValidKeywords(void)
{
	std::map<std::string, bool> map;

	map[Token::Keyword::LOCATION] = true;
	map[Token::Keyword::ALLOW_METHODS] = true;
	map[Token::Keyword::CLIENT_MAX_BODY_SIZE] = true;
	map[Token::Keyword::ROOT] = true;
	map[Token::Keyword::INDEX] = true;
	map[Token::Keyword::RETURN] = true;
	map[Token::Keyword::AUTO_INDEX] = true;
	map[Token::Keyword::UPLOAD] = true;
	map[Token::Keyword::CGI] = true;

	return map;
}

bool parser::isValidServerKeyword(const std::list<Token>::const_iterator &it)
{
	static const std::map<std::string, bool> valid_keywords(initServerValidKeywords());
	try
	{
		return valid_keywords.at(it->getValue());
	}
	catch (...)
	{
		return false;
	}
}

bool parser::isValidLocationKeyword(const std::list<Token>::const_iterator &it)
{
	static const std::map<std::string, bool> valid_keywords(initLocationValidKeywords());
	try
	{
		return valid_keywords.at(it->getValue());
	}
	catch (...)
	{
		return false;
	}
}

bool parser::validate(const std::list<Token> &list)
{
	parser::t_rule f;
	std::list<Token>::const_iterator it = list.begin();

	if (list.empty())
		return false;
	if (it->getValue() != Token::Keyword::SERVER)
		return false;
	while (it != list.end())
	{
		if (it->getValue() == Token::Keyword::SERVER)
		{
			f = parser::rule::get(it);
			if (!f(it, list.end()))
				return false;
		}
		++it;
	}
	return true;
}
