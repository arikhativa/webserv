
#include <ServerConf/ServerConf.hpp>

const std::string ServerConf::DEFAULT_ROOT("/var/www/html");
const std::string ServerConf::DEFAULT_SERVER_NAME("");
const std::string ServerConf::DEFAULT_HTM("index.htm");
const std::string ServerConf::DEFAULT_HTML("index.html");

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ServerConf::ServerConf()
	: _max_body_size(0, false)
	, _return(NULL)
	, _root(NULL)
{
}

ServerConf::InvalidServerConf::InvalidServerConf(const std::string &msg)
	: _msg("Invalid ServerConf: " + msg)
{
}

ServerConf::InvalidServerConf::~InvalidServerConf() throw()
{
}

const char *ServerConf::InvalidServerConf::what() const throw()
{
	return _msg.c_str();
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
	o << std::boolalpha;

	o << "{"
	  << "\"_name\": " << i.getNames() << ", "
	  << "\"_max_body_size\": " << i.getMaxBodySize() << ", ";
	{
		const IReturn *ptr = i.getReturn();

		if (ptr)
			o << "\"_return\": " << *ptr << ", ";
	}

	{
		const IPath *ptr = i.getRoot();

		if (ptr)
			o << "\"_root\": \"" << ptr->get() << "\", ";
	}
	o << "\"_index_files\": " << i.getIndexFiles() << ", "
	  << "\"_error_pages\": " << i.getErrorPages() << ", "
	  << "\"_listen\": " << i.getListen() << ", "
	  << "\"_locations\": " << i.getLocations() << "}";
	return o;
}

std::ostream &operator<<(std::ostream &o, const IServerConf &i)
{
	const ServerConf &tmp = dynamic_cast<const ServerConf &>(i);
	o << tmp;

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

const std::list<std::string> &ServerConf::getNames(void) const
{
	return _name;
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

void ServerConf::setDefaultSettingIfNeeded(void)
{
	if (_listen.empty())
		addListen(Listen());
	if (_name.empty())
		_name.push_back(DEFAULT_SERVER_NAME);
	if (!_root)
		_root = new Path(DEFAULT_ROOT);
	if (!_index_files.size())
	{
		_index_files.push_back(DEFAULT_HTML);
		_index_files.push_back(DEFAULT_HTM);
	}
}

void ServerConf::addName(const std::string &name)
{
	_name.push_back(name);
}
void ServerConf::setMaxBodySize(const std::string &size)
{
	if (_max_body_size.isOn())
		throw InvalidServerConf(Token::Keyword::CLIENT_MAX_BODY_SIZE + " is already set");
	std::size_t i = converter::stringToSizeT(size);
	_max_body_size.setValue(i);
	_max_body_size.setOn(true);
}

void ServerConf::setReturn(const std::string &status, const std::string &path)
{
	if (_return)
		throw InvalidServerConf(Token::Keyword::RETURN + " is already set");
	_return = new Return(status, path);
}

void ServerConf::setRoot(const std::string &path)
{
	if (_root)
		throw InvalidServerConf(Token::Keyword::ROOT + " is already set");
	if (!path.size())
		throw InvalidServerConf(Token::Keyword::ROOT + " can't be empty");
	_root = new Path(path);
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
	ErrorPage page(status, path);

	std::list<ErrorPage>::iterator it = _error_pages.begin();
	while (it != _error_pages.end())
	{
		if (it->getStatus().get() == page.getStatus().get())
			throw InvalidServerConf("Error page for status " + status + " is already set");
		++it;
	}
	_error_pages.push_back(page);
}

void ServerConf::addListenByPort(const std::string &port)
{
	Listen listen;

	listen.setPort(port);

	addListen(listen);
}

void ServerConf::addListenByIP(const std::string &ip)
{
	Listen listen;

	listen.setAddress(ip);

	addListen(listen);
}

void ServerConf::addListen(const std::string &ip, const std::string &port)
{
	Listen listen(ip, port);

	addListen(listen);
}

void ServerConf::addListen(const Listen &listen)
{
	std::list<Listen>::iterator it = _listen.begin();

	while (it != _listen.end())
	{
		if (it->getAddress().get() == listen.getAddress().get() && it->getPort().get() == listen.getPort().get())
		{
			std::string str(listen.getAddress().get());
			str += ":";
			std::string port = converter::numToString(listen.getPort().get());
			str += port;
			throw InvalidServerConf("Listen for Address: " + str + " is already set");
		}
		++it;
	}
	_listen.push_back(listen);
}

Location &ServerConf::createGetLocation(void)
{
	_locations.push_back(Location());
	return _locations.back();
}

/* ************************************************************************** */
