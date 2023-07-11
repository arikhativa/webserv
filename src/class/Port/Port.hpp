
#ifndef PORT_HPP
#define PORT_HPP

#include <arpa/inet.h>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

#include <IPort/IPort.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class Port : public IPort
{
  public:
	explicit Port(const std::string &port);
	explicit Port(uint16_t port);
	Port(Port const &src);
	virtual ~Port();

	Port &operator=(Port const &rhs);

	virtual uint16_t get(void) const;
	void set(uint16_t port);

	static bool isValid(int);
	class InvalidPortException : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

  private:
	uint16_t _port;
};

std::ostream &operator<<(std::ostream &o, Port const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* PORT_HPP */
