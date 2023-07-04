
#ifndef I_LOCATION_HPP
#define I_LOCATION_HPP

#include <iostream>
#include <string>

#include <IErrorPage/IErrorPage.hpp>
#include <IIndexFiles/IIndexFiles.hpp>
#include <ILimitExcept/ILimitExcept.hpp>
#include <IMaxBodySize/IMaxBodySize.hpp>
#include <IPath/IPath.hpp>
#include <IReturn/IReturn.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class ILocation
{
  public:
	virtual IPath &getRoot(void) const = 0;
	virtual ~ILocation() = default;
	virtual IIndexFiles &getIndexFiles(void) const = 0;
	virtual ILimitExcept &getLimitExcept(void) const = 0;
	virtual IReturn &getReturn(void) const = 0;
	virtual std::list<IErrorPage &> getErrorPages(void) const = 0;
	virtual bool isAutoIndexOn(void) const = 0;
	virtual IMaxBodySize &getMaxBodySize(void) const = 0;
	virtual bool canUpload(void) const = 0;
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_LOCATION_HPP */
