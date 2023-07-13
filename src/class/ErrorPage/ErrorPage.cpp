
#include <ErrorPage/ErrorPage.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ErrorPage::ErrorPage(const std::string &status, const std::string &path)
	: _status(status)
	, _path(path)
{
}

ErrorPage::ErrorPage(const HTTPStatusCode &status, const Path &path)
	: _status(status)
	, _path(path)
{
}

ErrorPage::ErrorPage(const ErrorPage &src)
	: _status(src.getStatus())
	, _path(src.getPath().get())
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
		_status = rhs.getStatus();
		_path.set(rhs.getPath().get());
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, ErrorPage const &i)
{
	o << "ErrorPage[" << i.getStatus().get() << " " << i.getPath().get() << "]";
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
	return _status;
}

const IPath &ErrorPage::getPath(void) const
{
	return _path;
}

void ErrorPage::setStatus(HTTPStatusCode status)
{
	_status = status;
}

void ErrorPage::setPath(const Path &path)
{
	_path = path;
}

void ErrorPage::setStatus(const std::string &status)
{
	_status.set(status);
}

void ErrorPage::setPath(const std::string &path)
{
	_path.set(path);
}

/* ************************************************************************** */
