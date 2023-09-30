
#include <builder/builder.hpp>

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

static void checkLocationCGIAndUpload(const std::list< const ILocation * > &list)
{
	std::list< const ILocation * >::const_iterator it = list.begin();
	std::list< const ILocation * >::const_iterator end = list.end();

	while (it != end)
	{
		if ((*it)->getCGIConf().isSet() && (*it)->getUploadStore())
			throw std::runtime_error("Location cannot have both CGI and upload_store");
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

static void validateNoCGIAndUpload(const IConf *conf)
{
	std::map< std::string, bool > names;
	std::list< const IServerConf * > servers = conf->getServers();
	std::list< const IServerConf * >::const_iterator server = servers.begin();

	while (server != servers.end())
	{
		std::list< const ILocation * > list = (*server)->getLocations();
		checkLocationCGIAndUpload(list);
		++server;
	}
}

void builder::validate(const IConf *conf)
{
	validateNoDupNames(conf);
	validateNoDupLocations(conf);
	validateNoCGIAndUpload(conf);
}
