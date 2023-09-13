
#include <ErrorPageSet/ErrorPageSet.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ErrorPageSet::ErrorPageSet()
	: _pages(defaultPager::getPages())
{
}

ErrorPageSet::ErrorPageSet(const ErrorPageSet &src)
	: _pages(src._pages)
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ErrorPageSet::~ErrorPageSet()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ErrorPageSet &ErrorPageSet::operator=(ErrorPageSet const &rhs)
{
	if (this != &rhs)
	{
		this->_pages = rhs.getPages();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, ErrorPageSet const &i)
{
	o << i.getPages();
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

void ErrorPageSet::setRoot(const std::string &root)
{
	_root = Path(root);
}

void ErrorPageSet::setRoot(const Path &root)
{
	_root = root;
}

void ErrorPageSet::setPage(HTTPStatusCode::Code code, const std::string &page)
{
	if (page[0] == '/')
		_pages[code] = _root.get() + page;
	else
		_pages[code] = _root.get() + "/" + page;
}

std::string ErrorPageSet::getPage(HTTPStatusCode::Code code) const
{
	try
	{
		return _pages.at(code);
	}
	catch (...)
	{
		return "";
	}
}

const std::map<HTTPStatusCode::Code, std::string> &ErrorPageSet::getPages(void) const
{
	return _pages;
}

/* ************************************************************************** */
