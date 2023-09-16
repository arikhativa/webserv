
#include <matcher/matcher.hpp>

static bool matchByListen(const IServerConf *s, const IListen *socket)
{
	std::list<const IServerConf *> ret;
	std::list<const IListen *> list = s->getListen();
	std::list<const IListen *>::const_iterator it = list.begin();

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

static const IServerConf *getDefaultServerByListen(const std::list<const IServerConf *> &list, const IListen *socket)
{
	std::list<const IServerConf *>::const_iterator it = list.begin();

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
	std::list<std::string> list = s->getNames();
	std::list<std::string>::const_iterator it = list.begin();
	std::map<std::string, std::string> headers = req.getHeaders();

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
	std::list<const IServerConf *> list = conf->getServers();
	std::list<const IServerConf *>::const_iterator it = list.begin();

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
	std::list<const ILocation *> list = s->getLocations();
	std::list<const ILocation *>::const_iterator tmp = list.end();
	std::list<const ILocation *>::const_iterator it = list.begin();
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

void matcher::cgiToResponse(const std::string &_cgi, ResponseHeader &response)
{
	if (_cgi.find(httpConstants::HEADER_BREAK) == std::string::npos)
		return (response.setBody(_cgi));

	std::map<std::string, std::string> _headers;
	std::size_t start = 0;
	std::size_t end = _cgi.find(httpConstants::FIELD_BREAK, start);

	if (end == std::string::npos)
		throw ABaseHTTPCall::Incomplete("Bad header: missing end of the first header");
	while (end != std::string::npos && end <= _cgi.find(httpConstants::HEADER_BREAK) && start != end)
	{
		std::size_t colon_pos = _cgi.find(":", start);
		if (colon_pos > end)
			throw ABaseHTTPCall::Invalid("Bad header: missing colon");

		std::string key = converter::toNginxStyle(_cgi.substr(start, colon_pos - start));

		colon_pos += 2;
		std::string value = _cgi.substr(colon_pos, end - colon_pos);
		if (ABaseHTTPCall::isKeyRestricted(key) && !_headers[key].empty())
			throw ABaseHTTPCall::Invalid("Bad header: duplicate restricted key: " + key);
		if (_headers[key].empty())
			_headers[key] = value;
		else
			_headers[key] += ", " + value;
		start = end + 2;
		end = _cgi.find(httpConstants::FIELD_BREAK, start);
	}
	for (std::map<std::string, std::string>::const_iterator it = _headers.begin(); it != _headers.end(); ++it)
	{
		response.setHeader(it->first, it->second);
	}
	response.setBody(_cgi.substr(_cgi.find(httpConstants::HEADER_BREAK) + httpConstants::HEADER_BREAK.length() + 1));
}