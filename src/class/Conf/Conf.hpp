
#ifndef CONF_HPP
#define CONF_HPP

#include <iostream>
#include <string>

#include <IConf/IConf.hpp>
#include <IServerConf/IServerConf.hpp>
#include <Path/Path.hpp>
#include <ServerConf/ServerConf.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class Conf : public IConf
{
  public:
	explicit Conf(const std::string &file_name);
	virtual ~Conf();

	virtual std::list< const IServerConf * > getServers(void) const;
	virtual std::string getFileName(void) const;

	ServerConf &createGetServer(void);
	void addDefaultServerIfNeeded(void);

  private:
	Conf(Conf const &src);
	Conf &operator=(Conf const &rhs);

	Path _file;
	std::list< ServerConf > _servers;
};

std::ostream &operator<<(std::ostream &o, const Conf &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* CONF_HPP */
