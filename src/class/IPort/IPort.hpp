
#ifndef I_PORT_HPP
#define I_PORT_HPP

#include <arpa/inet.h>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class IPort
{
  public:
	virtual ~IPort(){};
	virtual uint16_t get(void) const = 0;
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_PORT_HPP */
