
#include <ServerConf/ServerConf.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ServerConf::ServerConf()
	: _name("", false)
	, _max_body_size(0, false)
	, _return(NULL)
	, _root(NULL)
{
}

ServerConf::InvalidServerConf::InvalidServerConf(const std::string &msg)
	: _msg(msg)
{
}

ServerConf::InvalidServerConf::~InvalidServerConf() throw()
{
}

const char *ServerConf::InvalidServerConf::what() const throw()
{
	std::string tmp("Invalid ServerConf: " + _msg);
	return tmp.c_str();
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ServerConf::~ServerConf()
{
	if (_return)
		delete _return;
	if (_root)
		delete _root;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

std::ostream &operator<<(std::ostream &o, ServerConf const &i)
{
	(void)i;
	o << "{"
	  << "}";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/
/*
** ------------------------------------ GET ------------------------------------
*/

std::string ServerConf::getName(void) const
{
	if (_name.isOn())
		return _name.getValue();
	return "";
}

std::size_t ServerConf::getMaxBodySize(void) const
{
	if (_max_body_size.isOn())
		return _max_body_size.getValue();
	return 0;
}

const IReturn *ServerConf::getReturn(void) const
{
	return _return;
}

const IPath *ServerConf::getRoot(void) const
{
	return _root;
}

const std::list<std::string> &ServerConf::getIndexFiles(void) const
{
	return _index_files;
}

std::list<const IErrorPage *> ServerConf::getErrorPages(void) const
{
	std::list<const IErrorPage *> ret;
	const ErrorPage *tmp;

	for (std::list<ErrorPage>::const_iterator it = _error_pages.begin(); it != _error_pages.end(); ++it)
	{
		tmp = &(*it);
		ret.push_back(tmp);
	}
	return ret;
}

std::list<const IListen *> ServerConf::getListen(void) const
{
	std::list<const IListen *> ret;
	const IListen *tmp;

	for (std::list<Listen>::const_iterator it = _listen.begin(); it != _listen.end(); ++it)
	{
		tmp = &(*it);
		ret.push_back(tmp);
	}
	return ret;
}

std::list<const ILocation *> ServerConf::getLocations(void) const
{
	std::list<const ILocation *> ret;
	const ILocation *tmp;

	for (std::list<Location>::const_iterator it = _locations.begin(); it != _locations.end(); ++it)
	{
		tmp = &(*it);
		ret.push_back(tmp);
	}
	return ret;
}

/*
** ----------------------------------- SET -------------------------------------
*/

void ServerConf::setName(const std::string &name)
{
}

void ServerConf::setMaxBodySize(const std::string &size)
{
}

void ServerConf::setReturn(const std::string &status, const std::string &path)
{
}

void ServerConf::setRoot(const std::string &path)
{
}

void ServerConf::setIndexFiles(const std::list<std::string> &index_files)
{
	if (_index_files.size())
		throw InvalidServerConf(Token::Keyword::INDEX + " is already set");
	if (!index_files.size())
		throw InvalidServerConf(Token::Keyword::INDEX + " can't be empty");
	std::list<std::string>::const_iterator it = index_files.begin();
	while (it != index_files.end())
	{
		_index_files.push_back(*it);
		++it;
	}
}
void ServerConf::addErrorPage(const std::string &status, const std::string &path)
{
}

void ServerConf::addListenByPort(const std::string &port)
{
}

void ServerConf::addListenByIP(const std::string &ip)
{
}

void ServerConf::addListen(const std::string &ip, const std::string &port)
{
}

void ServerConf::addLocation(const Location &location)
{
}

/* ************************************************************************** */
