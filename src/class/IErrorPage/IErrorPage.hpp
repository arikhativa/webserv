
#ifndef I_ERROR_PAGE_HPP
#define I_ERROR_PAGE_HPP

#include <iostream>
#include <string>

#include <HTTPStatusCode/HTTPStatusCode.hpp>
#include <IPath/IPath.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

// TODO maybe HTTPStatusCode should be an interface
class IErrorPage
{
  public:
	virtual ~IErrorPage(){};
	virtual HTTPStatusCode getStatus(void) const = 0;
	virtual const IPath &getPath(void) const = 0;
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_ERROR_PAGE_HPP */
