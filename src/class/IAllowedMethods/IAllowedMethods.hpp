
#ifndef I_ALLOWED_METHODS_HPP
#define I_ALLOWED_METHODS_HPP

#include <iostream>
#include <string>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class IAllowedMethods
{
  public:
	virtual ~IAllowedMethods(){};
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_ALLOWED_METHODS_HPP */
