
#include <CGIConf/CGIConf.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

CGIConf::CGIConf()
	: _extension("")
	, _path("")
{
}

CGIConf::CGIConf(const CGIConf &src)
	: _extension(src._extension)
	, _path(src._path)
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

CGIConf::~CGIConf()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

CGIConf &CGIConf::operator=(CGIConf const &rhs)
{
	if (this != &rhs)
	{
		this->_extension = rhs.getExtension();
		this->_path = rhs.getPath();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, CGIConf const &i)
{
	o << "{ \"_extension\": \"" << i.getExtension() << "\", \"_path\": \"" << i.getPath() << "\" }";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

bool CGIConf::isSet(void) const
{
	return !this->_extension.empty() && !this->_path.get().empty();
}

void CGIConf::setExtension(const std::string &ext)
{
	this->_extension = ext;
}

void CGIConf::setPath(const std::string &path)
{
	this->_path.set(path);
}

std::string CGIConf::getExtension(void) const
{
	return this->_extension;
}

const Path &CGIConf::getPath(void) const
{
	return this->_path;
}

/* ************************************************************************** */
