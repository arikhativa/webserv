
#ifndef I_RETURN_HPP
#define I_RETURN_HPP

#include <iostream>
#include <string>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class IReturn
{
  public:
	virtual ~IReturn(){};
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_RETURN_HPP */
