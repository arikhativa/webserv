
#include <ErrorPage/ErrorPage.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ErrorPage::ErrorPage(const std::string &status, const std::string &path)
	: BasePairCodePath(status, path)
{
}

ErrorPage::ErrorPage(const HTTPStatusCode &status, const Path &path)
	: BasePairCodePath(status, path)
{
}

ErrorPage::ErrorPage(const ErrorPage &src)
	: BasePairCodePath(src)
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ErrorPage::~ErrorPage()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ErrorPage &ErrorPage::operator=(ErrorPage const &rhs)
{
	if (this != &rhs)
	{
		this->setStatus(rhs.getStatus());
		this->setPath(rhs.getPath().get());
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, ErrorPage const &i)
{
	o << "ErrorPage[" << i.getStatus().get() << " " << i.getPath().get() << "]";
	return o;
}

std::ostream &operator<<(std::ostream &o, IErrorPage const &i)
{
	const ErrorPage &tmp = dynamic_cast<const ErrorPage &>(i);

	o << tmp;
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

HTTPStatusCode ErrorPage::getStatus(void) const
{
	return BasePairCodePath::getStatus();
}

const IPath &ErrorPage::getPath(void) const
{
	return BasePairCodePath::getPath();
}

/* ************************************************************************** */
