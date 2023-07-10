
#include <Location/Location.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Location::Location()
	: _path(NULL)
	, _auto_index(false, false)
	, _upload(false, false)
	, _max_body_size(0, false)
	, _allowed_methods(NULL)
	, _return(NULL)
{
}

Location::InvalidLocationException::InvalidLocationException(const std::string &msg)
	: _msg(msg)
{
}

Location::InvalidLocationException::~InvalidLocationException() throw()
{
}

const char *Location::InvalidLocationException::what() const throw()
{
	std::string tmp("Invalid location: " + _msg);
	return tmp.c_str();
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Location::~Location()
{
	if (_return)
		delete _return;
	if (_path)
		delete _path;
	if (_allowed_methods)
		delete _allowed_methods;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

std::ostream &operator<<(std::ostream &o, Location const &i)
{
	o << std::boolalpha;

	const IReturn *ptr = i.getReturn();

	o << "{"
	  << "\"_path\": \"" << i.getPath().get() << "\", "
	  << "\"_auto_index\": " << i.isAutoIndexOn() << ", "
	  << "\"_upload\": " << i.canUpload() << ", "
	  << "\"_max_body_size\": " << i.getMaxBodySize() << ", "
	  << "\"_allowed_methods\": " << i.getAllowedMethods() << ", ";

	if (ptr)
		o << "\"_return\": " << *ptr << ", ";

	o << "\"_index_files\": " << i.getIndexFiles() << ", "
	  << "\"_error_pages\": " << i.getErrorPages() << "}";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void Location::setDefaultSettingIfNeeded(void)
{
	if (!_auto_index.isOn())
		setAutoIndex("off");
	if (!_upload.isOn())
		setUpload("off");
	if (!_allowed_methods)
	{
		_allowed_methods = new AllowedMethods();
		_allowed_methods->setGET(true);
		_allowed_methods->setPOST(true);
		_allowed_methods->setDELETE(true);
	}
	if (!_max_body_size.isOn())
		setMaxBodySize("0");
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

const IPath &Location::getPath(void) const
{
	return *_path;
}

const std::list<std::string> &Location::getIndexFiles(void) const
{
	return _index_files;
}

const IAllowedMethods &Location::getAllowedMethods(void) const
{
	return *_allowed_methods;
}

const IReturn *Location::getReturn(void) const
{
	return _return;
}

std::list<const IErrorPage *> Location::getErrorPages(void) const
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

std::size_t Location::getMaxBodySize(void) const
{
	if (_max_body_size.isOn())
		return _max_body_size.getValue();
	return 0;
}

bool Location::isAutoIndexOn(void) const
{
	if (_auto_index.isOn())
		return _auto_index.getValue();
	return false;
}

bool Location::canUpload(void) const
{
	if (_upload.isOn())
		return _upload.getValue();
	return false;
}

void Location::setPath(const std::string &path)
{
	if (!_path)
		_path = new Path(path);
}

void Location::setAutoIndex(const std::string &auto_index)
{
	if (_auto_index.isOn())
		throw InvalidLocationException(Token::Keyword::AUTO_INDEX + " is already set");
	_auto_index.setValue(converter::onOffStringToBool(auto_index));
	_auto_index.setOn(true);
}

void Location::setUpload(const std::string &upload)
{
	if (_upload.isOn())
		throw InvalidLocationException(Token::Keyword::UPLOAD + " is already set");
	_upload.setValue(converter::onOffStringToBool(upload));
	_upload.setOn(true);
}

void Location::setMaxBodySize(const std::string &max_body_size)
{
	if (_max_body_size.isOn())
		throw InvalidLocationException(Token::Keyword::CLIENT_MAX_BODY_SIZE + " is already set");
	std::size_t i = converter::stringToSizeT(max_body_size);
	_max_body_size.setValue(i);
	_max_body_size.setOn(true);
}

void Location::setReturn(const std::string &status, const std::string &path)
{
	if (_return)
		throw InvalidLocationException(Token::Keyword::RETURN + " is already set");
	_return = new Return(status, path);
}

void Location::setIndexFiles(const std::list<std::string> &index_files)
{
	if (_index_files.size())
		throw InvalidLocationException(Token::Keyword::INDEX + " is already set");
	if (!index_files.size())
		throw InvalidLocationException(Token::Keyword::INDEX + " can't be empty");
	std::list<std::string>::const_iterator it = index_files.begin();
	while (it != index_files.end())
	{
		_index_files.push_back(*it);
		++it;
	}
}

void Location::setAllowedMethods(const std::list<std::string> &allowed_methods)
{
	if (_allowed_methods)
		throw InvalidLocationException(Token::Keyword::ALLOW_METHODS + " is already set");
	if (!allowed_methods.size())
		throw InvalidLocationException(Token::Keyword::INDEX + " can't be empty");
	_allowed_methods = new AllowedMethods(allowed_methods);
}

void Location::addErrorPage(const std::string &status, const std::string &path)
{
	ErrorPage page(status, path);

	std::list<ErrorPage>::iterator it = _error_pages.begin();
	while (it != _error_pages.end())
	{
		if (it->getStatus().get() == page.getStatus().get())
			throw InvalidLocationException("Error page for status " + status + " is already set");
		++it;
	}
	_error_pages.push_back(page);
}

/* ************************************************************************** */