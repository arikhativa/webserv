
#include <Path/Path.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Path::Path()
	: _path("")
{
}

Path::Path(const std::string &path)
	: _path(path)
{
}

Path::Path(const Path &src)
	: _path(src.getPath())
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Path::~Path()
{
	_path = "";
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Path &Path::operator=(Path const &rhs)
{
	if (this != &rhs)
	{
		this->_path = rhs.getPath();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, Path const &i)
{
	o << "Path[" << i.getPath() << "]";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

bool Path::isRelative(void)
{
	if (this->_path.empty())
		return false;
	return (!isAbsolute());
}

bool Path::isAbsolute(void)
{
	if (this->_path.empty())
		return false;
	return (this->_path[0] == '/');
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

void Path::setPath(const std::string &path)
{
	this->_path = path;
}

const std::string &Path::getPath(void) const
{
	return this->_path;
}

/* ************************************************************************** */
