
#ifndef SERVER_CONF_HPP
#define SERVER_CONF_HPP

#include <iostream>
#include <string>

#include <IServerConf/IServerConf.hpp>
#include <Path/Path.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class ServerConf : public IServerConf
{
  public:
	ServerConf();
	ServerConf(ServerConf const &src);
	~ServerConf();

	ServerConf &operator=(ServerConf const &rhs);

	virtual std::string getName(void) const;
	virtual IPath *getRoot(void) const;
	virtual std::pair<IAddress *, IPort *> getListen(void) const;
	virtual IIndexFiles *getIndexFiles(void) const;
	virtual std::list<ILocation *> getLocations(void) const;
	virtual std::list<ICGILocation *> getCGILocation(void) const;
	virtual std::list<IErrorPage *> getErrorPages(void) const;
	virtual IReturn *getReturn(void) const;
	virtual std::size_t getMaxBodySize(void) const;

  private:
};

std::ostream &operator<<(std::ostream &o, ServerConf const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* SERVER_CONF_HPP */
