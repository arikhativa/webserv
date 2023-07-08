
#ifndef I_ADDRESS_HPP
#define I_ADDRESS_HPP

#include <iostream>
#include <string>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class IAddress
{
  public:
	virtual ~IAddress(){};
	virtual std::string getAddress(void) const = 0;
	virtual void setAddress(const std::string &address) = 0;
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_ADDRESS_HPP */
