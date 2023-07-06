
#include <ServerConf/ServerConf.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ServerConf::ServerConf()
{
}

ServerConf::ServerConf(const ServerConf &src)
{
	(void)src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ServerConf::~ServerConf()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ServerConf &ServerConf::operator=(ServerConf const &rhs)
{
	(void)rhs;
	return *this;
}

std::ostream &operator<<(std::ostream &o, ServerConf const &i)
{
	(void)i;
	o << "ServerConf["
	  << "]";
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
	return new Path();
}

std::pair<IAddress *, IPort *> ServerConf::getListen(void) const
{
	return std::pair<IAddress *, IPort *>(NULL, NULL);
}

IIndexFiles *ServerConf::getIndexFiles(void) const
{
	return NULL;
}

std::list<ILocation *> ServerConf::getLocations(void) const
{
	return std::list<ILocation *>();
}

std::list<ICGILocation *> ServerConf::getCGILocation(void) const
{
	return std::list<ICGILocation *>();
}

std::list<IErrorPage *> ServerConf::getErrorPages(void) const
{
	return std::list<IErrorPage *>();
}

IReturn *ServerConf::getReturn(void) const
{
	return NULL;
}

std::size_t ServerConf::getMaxBodySize(void) const
{
	return 0;
}

/* ************************************************************************** */
