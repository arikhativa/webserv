
#ifndef I_MAX_BODY_SIZE_HPP
#define I_MAX_BODY_SIZE_HPP

#include <iostream>
#include <string>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class IMaxBodySize
{
  public:
	virtual ~IMaxBodySize() = default;
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_MAX_BODY_SIZE_HPP */
