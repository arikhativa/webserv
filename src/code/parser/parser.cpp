
#include <parser/parser.hpp>

bool parser::isValidServerKeyword(const std::list<Token>::const_iterator &it)
{
	if (it->getValue() == "server")
		return false;
	return true;
}

// TODO think about "on" and "off"
bool parser::autoIndexRule(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end)
{
	++it;
	if (it == end)
		return false;
	if (it->getType() != Token::WORD)
		return false;
	if (it->getValue() != "on" && it->getValue() != "off")
		return false;
	++it;
	if (it == end)
		return false;
	if (it->getType() != Token::SEPARATOR)
		return false;
	return true;
}

bool parser::serverRule(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end)
{
	parser::t_rule f;
	int i = 0;

	++it;
	while (it != end)
	{
		if (it->getType() == Token::BLOCK_START)
			++i;
		else if (it->getType() == Token::BLOCK_END)
			--i;
		else if (it->getType() == Token::KEYWORD && !parser::isValidServerKeyword(it))
			return false;
		f = parser::getRule(it);
		if (f && !f(it, end))
			return false;
		++it;
	}
	return i == 0;
}

parser::t_rule parser::getRule(std::list<Token>::const_iterator it)
{
	if (it->getValue() == "server")
		return &parser::serverRule;
	if (it->getValue() == "autoindex")
		return &parser::autoIndexRule;
	return NULL;
}

// TODO think about "server"
bool parser::validate(const std::list<Token> &list)
{
	parser::t_rule f;
	std::list<Token>::const_iterator it = list.begin();

	if (list.empty())
		return false;
	if (it->getValue() != "server")
		return false;
	while (it != list.end())
	{
		if (it->getValue() == "server")
		{
			f = parser::getRule(it);
			if (!f(it, list.end()))
				return false;
		}
		++it;
	}
	return true;
}
