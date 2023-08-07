
#include <Conf/Conf.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Conf::Conf(const std::string &file_name)
	: _file(file_name)
{
	if (!Path::isValid(file_name))
		throw std::invalid_argument("Conf: file_name is not valid");
}

Conf::Conf(const Conf &src)
{
	(void)src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Conf::~Conf()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Conf &Conf::operator=(Conf const &rhs)
{
	(void)rhs;
	return *this;
}

std::ostream &operator<<(std::ostream &o, Conf const &i)
{
	o << "{\"_file\": \"" << i.getFileName() << "\", "
	  << "\"_servers\": " << i.getServers();

	o << "}";
	return o;
}

std::ostream &operator<<(std::ostream &o, const IConf &i)
{
	const Conf &tmp = dynamic_cast<const Conf &>(i);

	o << tmp;
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

ServerConf &Conf::createGetServer(void)
{
	_servers.push_back(ServerConf());
	return _servers.back();
}

void Conf::addDefaultServerIfNeeded(void)
{
	if (_servers.empty())
	{
		ServerConf &s = createGetServer();
		s.setDefaultSettingIfNeeded();
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::list<const IServerConf *> Conf::getServers(void) const
{
	std::list<const IServerConf *> ret;

	for (std::list<ServerConf>::const_iterator it = _servers.begin(); it != _servers.end(); ++it)
		ret.push_back(&(*it));
	return ret;
}

std::string Conf::getFileName(void) const
{
	return _file.get();
}

/* ************************************************************************** */
