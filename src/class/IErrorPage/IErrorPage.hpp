
#ifndef I_ERROR_PAGE_HPP
#define I_ERROR_PAGE_HPP

#include <iostream>
#include <string>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class IErrorPage
{
  public:
	virtual ~IErrorPage(){};
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_ERROR_PAGE_HPP */
