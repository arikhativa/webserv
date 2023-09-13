
#include <builder/builder.hpp>

static std::map<std::string, builder::location::t_rule> initRules(void)
{
	std::map<std::string, builder::location::t_rule> map;

	map[Token::Keyword::AUTO_INDEX] = &builder::location::autoIndex;
	map[Token::Keyword::UPLOAD] = &builder::location::upload;
	map[Token::Keyword::CLIENT_MAX_BODY_SIZE] = &builder::location::maxBodySize;
	map[Token::Keyword::ALLOW_METHODS] = &builder::location::allowedMethods;
	map[Token::Keyword::RETURN] = &builder::location::redirect;
	map[Token::Keyword::INDEX] = &builder::location::indexFiles;
	map[Token::Keyword::ERROR_PAGE] = &builder::location::errorPage;
	map[Token::Keyword::ROOT] = &builder::location::root;
	map[Token::Keyword::CGI] = &builder::location::cgi;
	return map;
}

builder::location::t_rule builder::location::get(std::list<Token>::const_iterator it)
{
	static const std::map<std::string, builder::location::t_rule> rules(initRules());
	try
	{
		return rules.at(it->getValue());
	}
	catch (...)
	{
		return NULL;
	}
}

void builder::location::path(Location &location, std::list<Token>::const_iterator it)
{
	++it;
	location.setPath(it->getValue());
}

void builder::location::autoIndex(Location &location, std::list<Token>::const_iterator it)
{
	++it;
	location.setAutoIndex(it->getValue());
}

void builder::location::upload(Location &location, std::list<Token>::const_iterator it)
{
	++it;
	location.setUpload(it->getValue());
}

void builder::location::maxBodySize(Location &location, std::list<Token>::const_iterator it)
{
	++it;
	location.setMaxBodySize(it->getValue());
}

void builder::location::allowedMethods(Location &location, std::list<Token>::const_iterator it)
{
	std::list<std::string> l;

	++it;
	while (it->getType() != Token::SEPARATOR)
	{
		l.push_back(it->getValue());
		++it;
	}
	location.setAllowedMethods(l);
}

void builder::location::redirect(Location &location, std::list<Token>::const_iterator it)
{
	++it;
	std::list<Token>::const_iterator tmp = it;

	++tmp;
	location.setReturn(it->getValue(), tmp->getValue());
}

void builder::location::indexFiles(Location &location, std::list<Token>::const_iterator it)
{
	std::list<std::string> l;

	++it;
	while (it->getType() != Token::SEPARATOR)
	{
		l.push_back(it->getValue());
		++it;
	}
	location.setIndexFiles(l);
}

void builder::location::errorPage(Location &location, std::list<Token>::const_iterator it)
{
	++it;
	std::list<Token>::const_iterator next = it;

	++next;
	location.addErrorPage(it->getValue(), next->getValue());
}

void builder::location::root(Location &location, std::list<Token>::const_iterator it)
{
	++it;
	location.setRoot(it->getValue());
}

void builder::location::cgi(Location &location, std::list<Token>::const_iterator it)
{
	++it;
	std::list<Token>::const_iterator tmp = it;

	++tmp;
	location.setCGI(it->getValue(), tmp->getValue());
}
