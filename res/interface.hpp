
#ifndef REPLACE_HPP
#define REPLACE_HPP

#include <iostream>
#include <string>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class Replace
{
  public:
	virtual ~Replace() = default;
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* REPLACE_HPP */
