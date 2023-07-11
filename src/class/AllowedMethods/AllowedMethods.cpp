
#include <AllowedMethods/AllowedMethods.hpp>

const std::string AllowedMethods::GET("GET /");
const std::string AllowedMethods::POST("POST /");
const std::string AllowedMethods::DELETE("DELETE /");

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

AllowedMethods::AllowedMethods()
	: _get(false)
	, _post(false)
	, _delete(false)
{
}

AllowedMethods::AllowedMethods(const std::list<std::string> &methods)
	: _get(false)
	, _post(false)
	, _delete(false)
{
	std::list<std::string>::const_iterator it = methods.begin();
	while (it != methods.end())
	{
		if (*it == AllowedMethods::GET)
			setGET(true);
		else if (*it == AllowedMethods::POST)
			setPOST(true);
		else if (*it == AllowedMethods::DELETE)
			setDELETE(true);
		else
			throw InvalidMethodException();
		it++;
	}
}

AllowedMethods::AllowedMethods(const AllowedMethods &src)
	: _get(src.getGET())
	, _post(src.getPOST())
	, _delete(src.getDELETE())
{
}

const char *AllowedMethods::InvalidMethodException::what() const throw()
{
	return "Invalid method";
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

AllowedMethods::~AllowedMethods()
{
	_get = false;
	_post = false;
	_delete = false;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

AllowedMethods &AllowedMethods::operator=(AllowedMethods const &rhs)
{
	if (this != &rhs)
	{
		_get = rhs._get;
		_post = rhs._post;
		_delete = rhs._delete;
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, AllowedMethods const &i)
{

	std::string str = "";

	if (i.getGET())
		str += AllowedMethods::GET;
	if (i.getPOST())
	{
		if (str != "")
			str += ", ";
		str += AllowedMethods::POST;
	}
	if (i.getDELETE())
	{
		if (str != "")
			str += ", ";
		str += AllowedMethods::DELETE;
	}

	o << "AllowedMethods[" << str << "]";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

bool AllowedMethods::isAllowed(IAllowedMethods::type method) const
{
	if (method == IAllowedMethods::GET)
		return getGET();
	else if (method == IAllowedMethods::POST)
		return getPOST();
	else if (method == IAllowedMethods::DELETE)
		return getDELETE();
	return false;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

bool AllowedMethods::getGET(void) const
{
	return this->_get;
}

bool AllowedMethods::getPOST(void) const
{
	return this->_post;
}

bool AllowedMethods::getDELETE(void) const
{
	return this->_delete;
}

void AllowedMethods::setGET(bool b)
{
	this->_get = b;
}

void AllowedMethods::setPOST(bool b)
{
	this->_post = b;
}

void AllowedMethods::setDELETE(bool b)
{
	this->_delete = b;
}

/* ************************************************************************** */
