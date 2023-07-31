
#include <Port/Port.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Port::Port(const std::string &port)
	: _port(0)
{
	int p = std::atoi(port.c_str());

	if (!Port::isValid(p))
		throw InvalidPortException();
	this->_port = static_cast<uint16_t>(p);
}

Port::Port(uint16_t port)
	: _port(port)
{
}

Port::Port(const Port &src)
	: _port(src.get())
{
}

const char *Port::InvalidPortException::what() const throw()
{
	return "Invalid Port";
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Port::~Port()
{
	_port = 0;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Port &Port::operator=(Port const &rhs)
{
	if (this != &rhs)
	{
		this->_port = rhs.get();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, Port const &i)
{
	o << "Port[" << i.get() << "]";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

bool Port::isValid(int port)
{
	return port > 0 && port < 65535;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

void Port::set(uint16_t port)
{
	this->_port = port;
}

uint16_t Port::get(void) const
{
	return this->_port;
}

/* ************************************************************************** */
