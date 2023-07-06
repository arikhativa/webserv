
#include <Conf/Conf.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Conf::Conf(const std::string &file_name)
	: _file(file_name)
{
}

Conf::Conf(const Conf &src)
{
	(void)src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

// TODO delete list?
Conf::~Conf()
{
	_file.clear();
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
	o << "Conf[" << i.getFileName() << "]";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

void Conf::addServer(IServerConf *s)
{
	this->_servers.push_back(s);
}

std::string Conf::getFileName(void) const
{
	return this->_file;
}

std::list<IServerConf *> Conf::getServers(void) const
{
	return this->_servers;
}

/* ************************************************************************** */
