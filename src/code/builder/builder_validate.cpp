
#include <builder/builder.hpp>

static void validateNoDupNames(const IConf *conf)
{
	std::map<std::string, bool> names;
	std::list<const IServerConf *> servers = conf->getServers();
	std::list<const IServerConf *>::const_iterator server = servers.begin();

	while (server != servers.end())
	{
		std::list<std::string> list = (*server)->getName();
		std::list<std::string>::const_iterator it = list.begin();
		std::list<std::string>::const_iterator end = list.end();

		while (it != end)
		{
			if (names[*it])
				throw std::runtime_error("Server name is duplicated");
			names[*it] = true;
			++it;
		}
		++server;
	}
}

void builder::validate(const IConf *conf)
{
	validateNoDupNames(conf);
}
