
#include <Replace/Replace.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Replace::Replace()
	: _value(0)
{
}

Replace::Replace(int i)
	: _value(i)
{
}

Replace::Replace(const Replace &src)
	: _value(src.getValue())
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Replace::~Replace()
{
	_value = 0;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Replace &Replace::operator=(Replace const &rhs)
{
	if (this != &rhs)
	{
		this->_value = rhs.getValue();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, Replace const &i)
{
	o << "Replace[" << i.getValue() << "]";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

void Replace::_setValue(int value)
{
	this->_value = value;
}

int Replace::getValue(void) const
{
	return this->_value;
}

/* ************************************************************************** */
