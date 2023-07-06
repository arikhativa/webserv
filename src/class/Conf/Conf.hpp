
#ifndef CONF_HPP
#define CONF_HPP

#include <iostream>
#include <list>
#include <string>

#include <IConfig/IConfig.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class Conf : public IConfig
{
  public:
	explicit Conf(const std::string &file_name);
	virtual ~Conf();

	virtual std::list<IServerConf *> getServers(void) const;
	virtual std::string getFileName(void) const;

	void Conf::addServer(IServerConf *s);

  private:
	Conf(Conf const &src);
	Conf &operator=(Conf const &rhs);

	std::string _file;
	std::list<IServerConf *> _servers;
};

std::ostream &operator<<(std::ostream &o, Conf const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* CONF_HPP */
