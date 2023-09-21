
#include <matcher/matcher.hpp>

static bool matchByListen(const IServerConf *s, const IListen *socket)
{
	std::list< const IServerConf * > ret;
	std::list< const IListen * > list = s->getListen();
	std::list< const IListen * >::const_iterator it = list.begin();

	const IAddress &addr = socket->getAddress();
	const IPort &port = socket->getPort();

	while (it != list.end())
	{
		if ((*it)->getAddress().get() == addr.get() && (*it)->getPort().get() == port.get())
			return true;
		++it;
	}
	return false;
}

static const IServerConf *getDefaultServerByListen(const std::list< const IServerConf * > &list, const IListen *socket)
{
	std::list< const IServerConf * >::const_iterator it = list.begin();

	while (it != list.end())
	{
		if (matchByListen(*it, socket))
		{
			return *it;
		}
		++it;
	}
	return NULL;
}

static bool matchByHost(const IServerConf *s, const BasicHTTPRequest &req)
{
	std::list< std::string > list = s->getNames();
	std::list< std::string >::const_iterator it = list.begin();
	std::map< std::string, std::string > headers = req.getHeaders();

	while (it != list.end())
	{
		if (headers["Host"].size() && *it == headers["Host"])
			return true;
		++it;
	}
	return false;
}

const IServerConf *matcher::requestToServer(const IConf *conf, const IListen *socket,
											const BasicHTTPRequest &req) throw()
{
	std::list< const IServerConf * > list = conf->getServers();
	std::list< const IServerConf * >::const_iterator it = list.begin();

	while (it != list.end())
	{
		if (matchByListen(*it, socket) && matchByHost(*it, req))
		{
			return *it;
		}
		++it;
	}
	return getDefaultServerByListen(list, socket);
}

const ILocation *matcher::requestToLocation(const IServerConf *s, const BasicHTTPRequest &req) throw()
{
	std::list< const ILocation * > list = s->getLocations();
	std::list< const ILocation * >::const_iterator tmp = list.end();
	std::list< const ILocation * >::const_iterator it = list.begin();
	while (it != list.end())
	{
		if ((req.getPath().find((*it)->getPath().get()) == 0))
		{
			if ((tmp == list.end()) || ((*it)->getPath().get().length() > (*tmp)->getPath().get().length()))
				tmp = it;
		}
		it++;
	}
	if (tmp == list.end())
		return s->getRootLocation();
	return (*tmp);
}