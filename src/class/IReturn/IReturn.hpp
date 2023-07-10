
#ifndef I_RETURN_HPP
#define I_RETURN_HPP

#include <iostream>
#include <string>

#include <HTTPStatusCode/HTTPStatusCode.hpp>
#include <IPath/IPath.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

// TODO maybe HTTPStatusCode should be an interface
class IReturn
{
  public:
	virtual ~IReturn(){};
	virtual HTTPStatusCode getStatus(void) const = 0;
	virtual const IPath &getPath(void) const = 0;
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_RETURN_HPP */
