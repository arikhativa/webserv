
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

std::ostream &operator<<(std::ostream &o, const IReturn &i)
{
	const Return &tmp = dynamic_cast<const Return &>(i);

	o << tmp;
	return o;
}

std::ostream &operator<<(std::ostream &o, const Return &i)
{
	const BasePairCodePath &tmp = dynamic_cast<const BasePairCodePath &>(i);

	o << tmp;
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
