
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
	virtual const std::string &get(void) const = 0;
	virtual bool isRelative(void) = 0;
	virtual bool isAbsolute(void) = 0;
	virtual bool isEmpty(void) const = 0;
	virtual bool isDir(void) const = 0;
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_PATH_HPP */
