
#ifndef SERVER_CONF_HPP
#define SERVER_CONF_HPP

#include <iostream>
#include <string>

#include <IServerConf/IServerConf.hpp>
#include <OnOff/OnOff.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class ServerConf : public IServerConf
{
  public:
	ServerConf();
	~ServerConf();

  private:
};

std::ostream &operator<<(std::ostream &o, ServerConf const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* SERVER_CONF_HPP */
