
#include <parser/parser.hpp>

static std::map<std::string, parser::t_rule> initRules(void)
{
	std::map<std::string, parser::t_rule> map;

	map["server"] = &parser::rule::server;
	map["server_name"] = &parser::rule::serverName;
	map["root"] = &parser::rule::root;
	map["listen"] = &parser::rule::listen;
	map["index"] = &parser::rule::index;
	map["error_page"] = &parser::rule::errorPage;
	map["return"] = &parser::rule::redirect;
	map["client_max_body_size"] = &parser::rule::clientMaxBodySize;
	map[Token::STR_SEPARATOR] = &parser::rule::separator;
	map[Token::STR_TILDE] = &parser::rule::tilde;
	map[Token::STR_BLOCK_START] = &parser::rule::blockStart;
	map[Token::STR_BLOCK_END] = &parser::rule::blockEnd;

	map["location"] = &parser::rule::location;
	map["autoindex"] = &parser::rule::autoIndex;
	map["allow_methods"] = &parser::rule::allowMethods;
	map["upload"] = &parser::rule::upload;

	return map;
}

parser::t_rule parser::rule::get(std::list<Token>::const_iterator it)
{
	static const std::map<std::string, parser::t_rule> rules(initRules());
	try
	{
		return rules.at(it->getValue());
	}
	catch (...)
	{
		return NULL;
	}
}

bool parser::rule::server(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end)
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
		f = parser::rule::get(it);
		if (f && !f(it, end))
			return false;
		++it;
	}
	return i == 0;
}

bool parser::rule::location(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end)
{
	(void)it;
	(void)end;
	return true;
}

static bool genericManyWordRule(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end)
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

static bool genericTwoWordRule(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end)
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

static bool genericSingleWordRule(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end)
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

// TODO think about "on" and "off"
static bool genericOnOffRule(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end)
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

bool parser::rule::serverName(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end)
{
	return genericManyWordRule(it, end);
}

bool parser::rule::root(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end)
{
	return genericSingleWordRule(it, end);
}

bool parser::rule::listen(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end)
{
	return genericSingleWordRule(it, end);
}

bool parser::rule::index(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end)
{
	return genericManyWordRule(it, end);
}

bool parser::rule::errorPage(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end)
{
	return genericTwoWordRule(it, end);
}

bool parser::rule::redirect(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end)
{
	return genericTwoWordRule(it, end);
}

bool parser::rule::clientMaxBodySize(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end)
{
	return genericSingleWordRule(it, end);
}

// TODO maybe Only GET POST DELETE (maybe not in the syntax part)
bool parser::rule::allowMethods(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end)
{
	return genericManyWordRule(it, end);
}

bool parser::rule::autoIndex(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end)
{
	return genericOnOffRule(it, end);
}

bool parser::rule::upload(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end)
{
	return genericOnOffRule(it, end);
}

bool parser::rule::blockStart(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end)
{
	++it;
	if (it == end)
		return true;
	if (it->getType() == Token::KEYWORD || it->getType() == Token::BLOCK_END)
		return true;
	return false;
}

bool parser::rule::blockEnd(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end)
{
	++it;
	if (it == end)
		return true;
	if (it->getType() == Token::KEYWORD || it->getType() == Token::BLOCK_END)
		return true;
	return false;
}

bool parser::rule::tilde(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end)
{
	(void)it;
	(void)end;
	return true;
}

bool parser::rule::separator(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end)
{
	++it;
	if (it == end)
		return false;
	if (it->getType() == Token::KEYWORD || it->getType() == Token::BLOCK_END)
		return true;
	return false;
}