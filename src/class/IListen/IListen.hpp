
#ifndef I_LISTEN_HPP
#define I_LISTEN_HPP

#include <iostream>
#include <string>

#include <IAddress/IAddress.hpp>
#include <IPort/IPort.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class IListen
{
  public:
	virtual ~IListen(){};

	virtual const IAddress &getAddress(void) const = 0;
	virtual const IPort &getPort(void) const = 0;
};

std::ostream &operator<<(std::ostream &o, const IListen &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_LISTEN_HPP */
