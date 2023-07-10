
#include <BasePairCodePath/BasePairCodePath.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

BasePairCodePath::BasePairCodePath(const std::string &status, const std::string &path)
	: _status(status)
	, _path(path)
{
	if (path.empty())
		throw InvalidPathException();
}

BasePairCodePath::BasePairCodePath(const HTTPStatusCode &status, const Path &path)
	: _status(status)
	, _path(path)
{
	if (path.get().empty())
		throw InvalidPathException();
}

BasePairCodePath::BasePairCodePath(const BasePairCodePath &src)
	: _status(src.getStatus())
	, _path(src.getPath().get())
{
}

const char *BasePairCodePath::InvalidPathException::what() const throw()
{
	return "Invalid path";
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

BasePairCodePath::~BasePairCodePath()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

BasePairCodePath &BasePairCodePath::operator=(BasePairCodePath const &rhs)
{
	if (this != &rhs)
	{
		_status = rhs.getStatus();
		_path.set(rhs.getPath().get());
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, const BasePairCodePath &i)
{
	o << "{";
	o << "\"_status\": " << i.getStatus().get() << ", ";
	o << "\"_path\": \"" << i.getPath().get() << "\"";
	o << "}";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

HTTPStatusCode BasePairCodePath::getStatus(void) const
{
	return _status;
}

const IPath &BasePairCodePath::getPath(void) const
{
	return _path;
}

void BasePairCodePath::setStatus(HTTPStatusCode status)
{
	_status = status;
}

void BasePairCodePath::setPath(const Path &path)
{
	_path = path;
}

void BasePairCodePath::setStatus(const std::string &status)
{
	_status.set(status);
}

void BasePairCodePath::setPath(const std::string &path)
{
	_path.set(path);
}

/* ************************************************************************** */
