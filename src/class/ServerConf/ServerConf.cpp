
#include <ServerConf/ServerConf.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ServerConf::ServerConf()
	: _value(0)
{
}

ServerConf::ServerConf(int i)
	: _value(i)
{
}

ServerConf::ServerConf(const ServerConf &src)
	: _value(src.getValue())
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ServerConf::~ServerConf()
{
	_value = 0;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ServerConf &ServerConf::operator=(ServerConf const &rhs)
{
	if (this != &rhs)
	{
		this->_value = rhs.getValue();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, ServerConf const &i)
{
	o << "ServerConf[" << i.getValue() << "]";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/
std::string ServerConf::getName(void) const
{
	return "";
}

IPath *ServerConf::getRoot(void) const
{
}

std::pair<IAddress *, IPort *> ServerConf::getListen(void) const
{
}

IIndexFiles ServerConf::getIndexFiles(void) const
{
}

std::list<ILocation *> ServerConf::getLocations(void) const
{
}

std::list<ICGILocation *> ServerConf::getCGILocation(void) const
{
}

std::list<IErrorPage *> ServerConf::getErrorPages(void) const
{
}

IReturn ServerConf::getReturn(void) const
{
}

std::size_t ServerConf::getMaxBodySize(void) const
{
}

/* ************************************************************************** */
