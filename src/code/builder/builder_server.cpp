
#include <builder/builder.hpp>

static std::map< std::string, builder::server::t_rule > initRules(void)
{
	std::map< std::string, builder::server::t_rule > map;

	map[Token::Keyword::SERVER_NAME] = &builder::server::serverName;
	map[Token::Keyword::ROOT] = &builder::server::root;
	map[Token::Keyword::LISTEN] = &builder::server::listen;
	map[Token::Keyword::INDEX] = &builder::server::index;
	map[Token::Keyword::ERROR_PAGE] = &builder::server::errorPage;
	map[Token::Keyword::RETURN] = &builder::server::redirect;
	map[Token::Keyword::CLIENT_MAX_BODY_SIZE] = &builder::server::clientMaxBodySize;
	map[Token::Keyword::LOCATION] = &builder::server::location;

	return map;
}

builder::server::t_rule builder::server::get(std::list< Token >::const_iterator it)
{
	static const std::map< std::string, builder::server::t_rule > rules(initRules());
	try
	{
		return rules.at(it->getValue());
	}
	catch (...)
	{
		return NULL;
	}
}

void builder::server::location(ServerConf &server, std::list< Token >::const_iterator it)
{
	builder::location::t_rule f;
	Location &location = server.createGetLocation();
	int block = 1;

	++it;
	location.setPath(it->getValue());
	++it;
	++it;
	while (block)
	{
		if (it->getType() == Token::BLOCK_END)
			--block;
		if (it->getType() == Token::BLOCK_START)
			++block;
		f = builder::location::get(it);
		if (f)
			f(location, it);
		++it;
	}
}

void builder::server::serverName(ServerConf &server, std::list< Token >::const_iterator it)
{
	++it;
	while (it->getType() != Token::SEPARATOR)
	{
		std::string tmp = it->getValue();

		server.addName(converter::removeQuotesIfNeeded(tmp));
		++it;
	}
}

void builder::server::root(ServerConf &server, std::list< Token >::const_iterator it)
{
	++it;
	std::string tmp = it->getValue();
	if (tmp[tmp.size() - 1] == '/')
		tmp = tmp.substr(0, tmp.size() - 1);
	server.setRoot(tmp);
}

void builder::server::listen(ServerConf &server, std::list< Token >::const_iterator it)
{
	++it;

	try
	{
		Port port(it->getValue());
		server.addListenByPort(it->getValue());
		return;
	}
	catch (...)
	{
	}
	try
	{
		IP ip(it->getValue());
		server.addListenByIP(it->getValue());
		return;
	}
	catch (...)
	{
	}

	Listen l;

	std::size_t sep = it->getValue().find(':');
	l.setAddress(it->getValue().substr(0, sep));
	l.setPort(it->getValue().substr(sep + 1));
	server.addListen(l);
}

void builder::server::index(ServerConf &server, std::list< Token >::const_iterator it)
{
	std::list< std::string > list;

	++it;
	while (it->getType() != Token::SEPARATOR)
	{
		std::string tmp = it->getValue();
		if (tmp[0] == '/')
			tmp = tmp.substr(1);
		list.push_back(tmp);
		++it;
	}
	server.setIndexFiles(list);
}

void builder::server::errorPage(ServerConf &server, std::list< Token >::const_iterator it)
{
	++it;
	std::list< Token >::const_iterator tmp = it;

	++tmp;
	server.addErrorPage(it->getValue(), tmp->getValue());
}

void builder::server::redirect(ServerConf &server, std::list< Token >::const_iterator it)
{
	++it;
	std::list< Token >::const_iterator tmp = it;

	++tmp;
	server.setReturn(it->getValue(), tmp->getValue());
}

void builder::server::clientMaxBodySize(ServerConf &server, std::list< Token >::const_iterator it)
{
	++it;

	server.setMaxBodySize(it->getValue());
}
