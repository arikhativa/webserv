
#ifndef I_SERVER_CONF_HPP
#define I_SERVER_CONF_HPP

#include <iostream>
#include <list>
#include <string>
#include <utility>

#include <IAddress/IAddress.hpp>
#include <ICGILocation/ICGILocation.hpp>
#include <IErrorPage/IErrorPage.hpp>
#include <ILocation/ILocation.hpp>
#include <IPath/IPath.hpp>
#include <IPort/IPort.hpp>
#include <IReturn/IReturn.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class IServerConf
{
  public:
	virtual ~IServerConf(){};

	virtual std::string getName(void) const = 0;
	virtual IPath getRoot(void) const = 0;
	virtual std::pair<IAddress *, IPort *> getListen(void) const = 0;
	virtual const std::list<std::string> &getIndexFiles(void) const = 0;
	virtual IAllowedMethods getAllowedMethods(void) const = 0;
	virtual std::list<ILocation *> getLocations(void) const = 0;
	virtual std::list<ICGILocation *> getCGILocation(void) const = 0;
	virtual std::list<IErrorPage *> getErrorPages(void) const = 0;
	virtual const IReturn *getReturn(void) const = 0;
	virtual std::size_t getMaxBodySize(void) const = 0;
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_SERVER_CONF_HPP */
