
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
	: _path(src.get())
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
		this->_path = rhs.get();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, Path const &i)
{
	o << "Path[" << i.get() << "]";
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

void Path::set(const std::string &path)
{
	this->_path = path;
}

const std::string &Path::get(void) const
{
	return this->_path;
}

/* ************************************************************************** */
