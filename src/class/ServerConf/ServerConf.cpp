
#include <ServerConf/ServerConf.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ServerConf::ServerConf()
	: _value(0)
{
}

ServerConf::ServerConf(int i)
	: _value(i)
{
}

ServerConf::ServerConf(const ServerConf &src)
	: _value(src.getValue())
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ServerConf::~ServerConf()
{
	_value = 0;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ServerConf &ServerConf::operator=(ServerConf const &rhs)
{
	if (this != &rhs)
	{
		this->_value = rhs.getValue();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, ServerConf const &i)
{
	o << "ServerConf[" << i.getValue() << "]";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

void ServerConf::_setValue(int value)
{
	this->_value = value;
}

int ServerConf::getValue(void) const
{
	return this->_value;
}

/* ************************************************************************** */
