
#include <builder/builder.hpp>

static void skipBlock(std::list<Token>::const_iterator &it)
{
	int block = 1;

	while (it->getType() != Token::BLOCK_START)
		++it;
	while (block > 0)
	{
		if (it->getType() == Token::BLOCK_END)
			--block;
		if (block > 0)
			++it;
	}
}

void builder::creatServer(Conf &conf, std::list<Token>::const_iterator it)
{
	builder::server::t_rule f;
	ServerConf &server = conf.createGetServer();
	int block = 1;

	++it;
	++it;
	while (block)
	{
		if (it->getType() == Token::BLOCK_END)
			--block;
		if (it->getType() == Token::BLOCK_START)
			++block;
		f = builder::server::get(it);
		if (f)
			f(server, it);
		if (it->getValue() == Token::Keyword::LOCATION)
		{
			skipBlock(it);
			++block;
		}
		else
			++it;
	}
	server.setDefaultSettingIfNeeded();
}

void builder::initAllServers(Conf &conf, std::list<Token>::const_iterator &it,
							 const std::list<Token>::const_iterator &end)
{
	while (it != end)
	{
		if (it->getValue() == Token::Keyword::SERVER)
			creatServer(conf, it);
		++it;
	}
}

const IConf *builder::createConf(const std::string &file_name, const std::list<Token> &list)
{
	Conf *conf = new Conf(file_name);

	std::list<Token>::const_iterator begin = list.begin();

	initAllServers(*conf, begin, list.end());

	return conf;
}
