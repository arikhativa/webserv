
#include <Listen/Listen.hpp>

const std::string Listen::_defaultIP("0.0.0.0");
const uint16_t Listen::_defaultPort(80);

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Listen::Listen()
	: _address(_defaultIP)
	, _port(_defaultPort)
{
}

Listen::Listen(const std::string &ip, const std::string &port)
	: _address(ip)
	, _port(port)
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Listen::~Listen()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

std::ostream &operator<<(std::ostream &o, Listen const &i)
{
	o << "{ \"_address\": \"" << i.getAddress().get() << "\", \"_port\": " << i.getPort().get() << " }";
	return o;
}

std::ostream &operator<<(std::ostream &o, const IListen &i)
{
	const Listen &tmp = dynamic_cast< const Listen & >(i);

	o << tmp;
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

const IAddress &Listen::getAddress(void) const
{
	return _address;
}

const IPort &Listen::getPort(void) const
{
	return _port;
}

void Listen::setAddress(const std::string &ip)
{
	_address.setAddress(ip);
}

void Listen::setPort(const std::string &port)
{
	_port.set(port);
}

/* ************************************************************************** */
