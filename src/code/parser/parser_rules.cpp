
#include <parser/parser.hpp>

static std::map< std::string, parser::t_rule > initRules(void)
{
	std::map< std::string, parser::t_rule > map;

	map[Token::Keyword::SERVER] = &parser::rule::server;
	map[Token::Keyword::SERVER_NAME] = &parser::rule::serverName;
	map[Token::Keyword::ROOT] = &parser::rule::root;
	map[Token::Keyword::LISTEN] = &parser::rule::listen;
	map[Token::Keyword::INDEX] = &parser::rule::index;
	map[Token::Keyword::ERROR_PAGE] = &parser::rule::errorPage;
	map[Token::Keyword::RETURN] = &parser::rule::redirect;
	map[Token::Keyword::CLIENT_MAX_BODY_SIZE] = &parser::rule::clientMaxBodySize;
	map[Token::STR_SEPARATOR] = &parser::rule::separator;
	map[Token::STR_TILDE] = &parser::rule::tilde;
	map[Token::STR_BLOCK_START] = &parser::rule::blockStart;
	map[Token::STR_BLOCK_END] = &parser::rule::blockEnd;

	map[Token::Keyword::LOCATION] = &parser::rule::location;
	map[Token::Keyword::AUTO_INDEX] = &parser::rule::autoIndex;
	map[Token::Keyword::ALLOW_METHODS] = &parser::rule::allowMethods;
	map[Token::Keyword::UPLOAD_STORE] = &parser::rule::upload_store;
	map[Token::Keyword::CGI] = &parser::rule::cgi;

	return map;
}

parser::t_rule parser::rule::get(std::list< Token >::const_iterator it)
{
	static const std::map< std::string, parser::t_rule > rules(initRules());
	try
	{
		return rules.at(it->getValue());
	}
	catch (...)
	{
		return NULL;
	}
}

static bool skipBlock(std::list< Token >::const_iterator &it, const std::list< Token >::const_iterator &end)
{
	int blocks = 1;

	while (it != end && it->getType() != Token::BLOCK_START)
		++it;
	if (it == end)
		return false;
	++it;
	while (it != end && blocks > 0)
	{
		if (it->getType() == Token::BLOCK_START)
			++blocks;
		else if (it->getType() == Token::BLOCK_END)
			--blocks;
		if (blocks > 0 && it != end)
			++it;
	}
	return 0 == blocks;
}

bool parser::rule::server(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end)
{
	parser::t_rule f;
	bool block = false;

	++it;
	if (it == end || it->getType() != Token::BLOCK_START)
		return false;
	++it;
	while (it != end && !block)
	{
		if (it->getType() == Token::BLOCK_START)
			return false;
		else if (it->getType() == Token::BLOCK_END && block)
			return false;
		else if (it->getType() == Token::BLOCK_END)
			block = true;
		else if (it->getType() == Token::KEYWORD && !parser::isValidServerKeyword(it))
			return false;
		f = parser::rule::get(it);
		if (f && !f(it, end))
			return false;
		if (it->getValue() == Token::Keyword::LOCATION && !skipBlock(it, end))
			return false;
		else
			++it;
	}
	return block;
}

bool parser::rule::location(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end)
{
	parser::t_rule f;
	bool block = false;

	++it;
	if (it == end)
		return false;
	if (it->getType() == Token::TILDE)
	{
		++it;
		if (it == end)
			return false;
	}
	if (it->getType() != Token::WORD)
		return false;
	++it;
	if (it == end || it->getType() != Token::BLOCK_START)
		return false;
	++it;
	while (it != end && !block)
	{
		if (it->getType() == Token::BLOCK_START)
			return false;
		else if (it->getType() == Token::BLOCK_END && block)
			return false;
		else if (it->getType() == Token::BLOCK_END)
			block = true;
		else if (it->getType() == Token::KEYWORD && !parser::isValidLocationKeyword(it))
			return false;
		f = parser::rule::get(it);
		if (f && !f(it, end))
			return false;
		if (it->getValue() == Token::Keyword::LOCATION && !skipBlock(it, end))
			return false;
		else
			++it;
	}
	return block;
}

static bool genericManyWordRule(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end)
{
	++it;
	if (it == end)
		return false;
	while (it != end && it->getType() == Token::WORD)
		++it;
	if (it == end)
		return false;
	if (it->getType() != Token::SEPARATOR)
		return false;
	return true;
}

static bool genericTwoWordRule(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end)
{
	++it;
	if (it == end)
		return false;
	if (it->getType() != Token::WORD)
		return false;
	++it;
	if (it == end)
		return false;
	if (it->getType() != Token::WORD)
		return false;
	++it;
	if (it == end)
		return false;
	if (it->getType() != Token::SEPARATOR)
		return false;
	return true;
}

static bool genericSingleWordRule(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end)
{
	++it;
	if (it == end)
		return false;
	if (it->getType() != Token::WORD)
		return false;
	++it;
	if (it == end)
		return false;
	if (it->getType() != Token::SEPARATOR)
		return false;
	return true;
}

static bool genericOnOffRule(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end)
{
	++it;
	if (it == end)
		return false;
	if (it->getType() != Token::WORD)
		return false;
	++it;
	if (it == end)
		return false;
	if (it->getType() != Token::SEPARATOR)
		return false;
	return true;
}

bool parser::rule::serverName(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end)
{
	return genericManyWordRule(it, end);
}

bool parser::rule::root(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end)
{
	return genericSingleWordRule(it, end);
}

bool parser::rule::listen(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end)
{
	return genericSingleWordRule(it, end);
}

bool parser::rule::index(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end)
{
	return genericManyWordRule(it, end);
}

bool parser::rule::errorPage(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end)
{
	return genericTwoWordRule(it, end);
}

bool parser::rule::redirect(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end)
{
	return genericTwoWordRule(it, end);
}

bool parser::rule::clientMaxBodySize(std::list< Token >::const_iterator it,
									 const std::list< Token >::const_iterator &end)
{
	return genericSingleWordRule(it, end);
}

bool parser::rule::allowMethods(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end)
{
	return genericManyWordRule(it, end);
}

bool parser::rule::autoIndex(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end)
{
	return genericOnOffRule(it, end);
}

bool parser::rule::upload_store(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end)
{
	return genericSingleWordRule(it, end);
}

bool parser::rule::cgi(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end)
{
	return genericTwoWordRule(it, end);
}

bool parser::rule::blockStart(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end)
{
	++it;
	if (it == end)
		return true;
	if (it->getType() == Token::KEYWORD || it->getType() == Token::BLOCK_END)
		return true;
	return false;
}

bool parser::rule::blockEnd(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end)
{
	++it;
	if (it == end)
		return true;
	if (it->getType() == Token::KEYWORD || it->getType() == Token::BLOCK_END)
		return true;
	return false;
}

bool parser::rule::tilde(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end)
{
	++it;
	if (it == end)
		return true;
	if (it->getType() != Token::WORD)
		return false;
	return true;
}

bool parser::rule::separator(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end)
{
	++it;
	if (it == end)
		return false;
	if (it->getType() == Token::KEYWORD || it->getType() == Token::BLOCK_END)
		return true;
	return false;
}
