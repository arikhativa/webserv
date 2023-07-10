
#include <Return/Return.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Return::Return(const std::string &status, const std::string &path)
	: BasePairCodePath(status, path)
{
}

Return::Return(const HTTPStatusCode &status, const Path &path)
	: BasePairCodePath(status, path)
{
}

Return::Return(const Return &src)
	: BasePairCodePath(src)
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Return::~Return()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Return &Return::operator=(Return const &rhs)
{
	if (this != &rhs)
	{
		this->setStatus(rhs.getStatus());
		this->setPath(rhs.getPath().get());
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, Return const &i)
{
	o << "Return[" << i.getStatus().get() << " " << i.getPath().get() << "]";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

HTTPStatusCode Return::getStatus(void) const
{
	return BasePairCodePath::getStatus();
}

const IPath &Return::getPath(void) const
{
	return BasePairCodePath::getPath();
}

/* ************************************************************************** */
