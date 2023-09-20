
#include <IP/IP.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

IP::IP(const std::string &ip)
	: _ip(ip)
{
	if (!IP::isValid(_ip))
		throw IP::InvalidIPException();
}

IP::IP(const IP &src)
	: _ip(src.get())
{
}

const char *IP::InvalidIPException::what() const throw()
{
	return "Invalid IP address";
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

IP::~IP()
{
	_ip = "";
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

IP &IP::operator=(IP const &rhs)
{
	if (this != &rhs)
	{
		this->_ip = rhs.get();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, IP const &i)
{
	o << i.get();
	return o;
}

/*
** ------------------------------ STATIC METHODS -------------------------------
*/

static std::vector< int > stringToVector(const std::string &ip)
{
	std::vector< int > ipVector(4);
	std::string token;
	std::size_t end = 0;
	std::size_t start = 0;
	std::size_t vec_index = 0;

	while (ip[end] && vec_index < 4)
	{
		while (ip[end] && ip[end] != '.')
			++end;
		if (ip[end] == '.')
		{
			if (ip[end + 1] == '.')
				throw IP::InvalidIPException();
			token = ip.substr(start, end);
			ipVector[vec_index] = (std::atoi(token.c_str()));
			++end;
			start = end;
			++vec_index;
		}
	}
	token = ip.substr(start, end);
	ipVector[vec_index] = (std::atoi(token.c_str()));
	if (ipVector.size() != 4)
		throw IP::InvalidIPException();
	return ipVector;
}

bool IP::isValid(const std::string &ip)
{
	if (ip.empty())
		return false;
	if (ip.length() > 15 || ip.length() < 7)
		return false;
	if (ip.find_first_not_of("0123456789.") != std::string::npos)
		return false;

	std::vector< int > ipVector(stringToVector(ip));
	for (int i = 0; i < 4; i++)
	{
		if (ipVector[i] < 0 || ipVector[i] > 255)
			return false;
	}
	return true;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

void IP::setAddress(const std::string &address)
{
	if (IP::isValid(address))
		this->_ip = address;
}

std::string IP::get(void) const
{
	return this->_ip;
}

/* ************************************************************************** */
