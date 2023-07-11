
#include <HTTPRequestHandler/HTTPRequestHandler.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

HTTPRequestHandler::HTTPRequestHandler()
	: _value(0)
{
}

HTTPRequestHandler::HTTPRequestHandler(int i)
	: _value(i)
{
}

HTTPRequestHandler::HTTPRequestHandler(const HTTPRequestHandler &src)
	: _value(src.getValue())
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

HTTPRequestHandler::~HTTPRequestHandler()
{
	_value = 0;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

HTTPRequestHandler &HTTPRequestHandler::operator=(HTTPRequestHandler const &rhs)
{
	if (this != &rhs)
	{
		this->_value = rhs.getValue();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, HTTPRequestHandler const &i)
{
	o << "HTTPRequestHandler[" << i.getValue() << "]";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

void HTTPRequestHandler::_setValue(int value)
{
	this->_value = value;
}

int HTTPRequestHandler::getValue(void) const
{
	return this->_value;
}

/* ************************************************************************** */
