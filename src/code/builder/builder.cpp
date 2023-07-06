

#include <builder/builder.hpp>

IServerConf *builder::createServer(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end)
{
}

IConfig *createConf(const std::string &file_name, const std::list<Token> &list)
{
	Conf *conf = new Conf(file_name);

	std::list<Token>::const_iterator it = list.begin();
	while (it != list.end())
	{
		if (it->getValue() == Token::Keyword::SERVER)
		{
			IServerConf *server = builder::createServer(it, list.end());
			conf->addServer(server);
		}
		it++;
	}
	return (NULL);
}
