
#include <ExampleClass/ExampleClass.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ExampleClass::ExampleClass()
	: _value(0)
{
}

ExampleClass::ExampleClass(int i)
	: _value(i)
{
}

ExampleClass::ExampleClass(const ExampleClass &src)
	: _value(src.getValue())
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ExampleClass::~ExampleClass()
{
	_value = 0;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ExampleClass &ExampleClass::operator=(ExampleClass const &rhs)
{
	if (this != &rhs)
	{
		this->_value = rhs.getValue();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, ExampleClass const &i)
{
	o << "ExampleClass[" << i.getValue() << "]";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

void ExampleClass::_setValue(int value)
{
	this->_value = value;
}

int ExampleClass::getValue(void) const
{
	return this->_value;
}

/* ************************************************************************** */
