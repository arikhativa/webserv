
#ifndef I_LOCATION_HPP
#define I_LOCATION_HPP

#include <iostream>
#include <string>

#include <IAllowedMethods/IAllowedMethods.hpp>
#include <IErrorPage/IErrorPage.hpp>
#include <IIndexFiles/IIndexFiles.hpp>
#include <IPath/IPath.hpp>
#include <IReturn/IReturn.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class ILocation
{
  public:
	virtual IPath *getRoot(void) const = 0;
	virtual ~ILocation(){};
	virtual IIndexFiles getIndexFiles(void) const = 0;
	virtual IAllowedMethods getAllowedMethods(void) const = 0;
	virtual IReturn getReturn(void) const = 0;
	virtual std::list<IErrorPage *> getErrorPages(void) const = 0;
	virtual bool isAutoIndexOn(void) const = 0;
	virtual std::size_t getMaxBodySize(void) const = 0;
	virtual bool canUpload(void) const = 0;
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_LOCATION_HPP */
