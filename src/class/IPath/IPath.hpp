
#ifndef I_PATH_HPP
#define I_PATH_HPP

#include <iostream>
#include <string>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class IPath
{
  public:
	virtual ~IPath(){};
	virtual bool IsRelative() = 0;
	virtual bool IsAbsolute() = 0;
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_PATH_HPP */
