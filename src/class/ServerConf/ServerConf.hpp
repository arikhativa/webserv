
#ifndef SERVER_CONF_HPP
#define SERVER_CONF_HPP

#include <iostream>
#include <string>

#include <IListen/IListen.hpp>
#include <IServerConf/IServerConf.hpp>
#include <OnOff/OnOff.hpp>
#include <Path/Path.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class ServerConf : public IServerConf
{
  public:
	ServerConf();
	~ServerConf();

	// void setDefaultSettingIfNeeded(void);

	// virtual std::string getName(void) const;
	// virtual const IPath &getRoot(void) const;
	// virtual std::list<IListen *> getListen(void) const;
	// virtual const std::list<std::string> &getIndexFiles(void) const;
	// virtual IAllowedMethods getAllowedMethods(void) const;
	// virtual std::list<ILocation *> getLocations(void) const;
	// virtual std::list<ICGILocation *> getCGILocation(void) const;
	// virtual std::list<IErrorPage *> getErrorPages(void) const;
	// virtual const IReturn *getReturn(void) const;
	// virtual std::size_t getMaxBodySize(void) const;

  private:
	// std::string _name;
	// OnOff<Path> _root;
	// std::pair<IAddress *, IPort *> _listen;
};

std::ostream &operator<<(std::ostream &o, ServerConf const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* SERVER_CONF_HPP */
