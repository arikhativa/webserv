
#include <builder/builder.hpp>

// TODO maybe create execpt obj
static void validateNoDupNames(const IConf *conf)
{
	std::map< std::string, bool > names;
	std::list< const IServerConf * > servers = conf->getServers();
	std::list< const IServerConf * >::const_iterator server = servers.begin();

	while (server != servers.end())
	{
		std::list< std::string > list = (*server)->getNames();
		std::list< std::string >::const_iterator it = list.begin();
		std::list< std::string >::const_iterator end = list.end();

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

static void checkLocationList(const std::list< const ILocation * > &list)
{
	std::map< std::string, bool > names;
	std::list< const ILocation * >::const_iterator it = list.begin();
	std::list< const ILocation * >::const_iterator end = list.end();

	while (it != end)
	{
		if (names[(*it)->getPath().get()])
			throw std::runtime_error("Location path is duplicated");
		names[(*it)->getPath().get()] = true;
		++it;
	}
}

static void validateNoDupLocations(const IConf *conf)
{
	std::map< std::string, bool > names;
	std::list< const IServerConf * > servers = conf->getServers();
	std::list< const IServerConf * >::const_iterator server = servers.begin();

	while (server != servers.end())
	{
		std::list< const ILocation * > list = (*server)->getLocations();
		checkLocationList(list);
		++server;
	}
}

void builder::validate(const IConf *conf)
{
	validateNoDupNames(conf);
	validateNoDupLocations(conf);
}
