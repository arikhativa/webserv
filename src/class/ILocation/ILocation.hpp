
#ifndef I_LOCATION_HPP
#define I_LOCATION_HPP

#include <iostream>
#include <string>

#include <CGIConf/CGIConf.hpp>
#include <ErrorPageSet/ErrorPageSet.hpp>
#include <IAllowedMethods/IAllowedMethods.hpp>
#include <IErrorPage/IErrorPage.hpp>
#include <IPath/IPath.hpp>
#include <IReturn/IReturn.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class ILocation
{
  public:
	virtual ~ILocation(){};
	virtual const IPath &getPath(void) const = 0;
	virtual const std::list< std::string > &getIndexFiles(void) const = 0;
	virtual const IAllowedMethods &getAllowedMethods(void) const = 0;
	virtual const IReturn *getReturn(void) const = 0;
	virtual std::list< const IErrorPage * > getErrorPages(void) const = 0;
	virtual std::size_t getMaxBodySize(void) const = 0;
	virtual bool isAutoIndexOn(void) const = 0;
	virtual const IPath *getRoot(void) const = 0;
	virtual const IPath *getUploadStore(void) const = 0;
	virtual const CGIConf &getCGIConf(void) const = 0;
	virtual const ErrorPageSet &getErrorPageSet(void) const = 0;
};

std::ostream &operator<<(std::ostream &o, const ILocation &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_LOCATION_HPP */
