
#ifndef I_PORT_HPP
#define I_PORT_HPP

#include <iostream>
#include <string>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class IPort
{
  public:
	virtual ~IPort() = default;
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_PORT_HPP */
