
#ifndef I_CONF_HPP
#define I_CONF_HPP

#include <iostream>
#include <string>

#include <IServerConf/IServerConf.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class IConf
{
  public:
	virtual ~IConf(){};

	virtual std::list< const IServerConf * > getServers(void) const = 0;
	virtual std::string getFileName(void) const = 0;
};

std::ostream &operator<<(std::ostream &o, const IConf &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_CONF_HPP */
