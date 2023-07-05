
#ifndef I_CONFIG_HPP
#define I_CONFIG_HPP

#include <iostream>
#include <list>
#include <string>

#include <IServerConf/IServerConf.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class IConfig
{
  public:
	virtual ~IConfig(void){};

	virtual std::list<IServerConf *> getServers(void) const = 0;
	virtual std::string getFileName(void) const = 0;
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_CONFIG_HPP */
