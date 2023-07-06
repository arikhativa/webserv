
#ifndef I_LIMIT_EXCEPT_HPP
#define I_LIMIT_EXCEPT_HPP

#include <iostream>
#include <string>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class ILimitExcept
{
  public:
	virtual ~ILimitExcept() = default;
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_LIMIT_EXCEPT_HPP */
