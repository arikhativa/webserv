
#ifndef CONF_FILE_HPP
#define CONF_FILE_HPP

#include <fstream>
#include <iostream>
#include <list>
#include <string>

#include <IConfig/IConfig.hpp>
#include <IServerConf/IServerConf.hpp>
#include <Token/Token.hpp>
#include <lexer/lexer.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class ConfFile : public IConfig
{
  public:
	explicit ConfFile(const std::string &file);
	virtual ~ConfFile();

	virtual std::list<IServerConf *> getServers(void) const;
	virtual std::string getFileName(void) const;

  private:
	ConfFile(ConfFile const &src);
	ConfFile &operator=(ConfFile const &rhs);

	std::string _fileName;
	std::list<IServerConf *> _servers;
};

std::ostream &operator<<(std::ostream &o, ConfFile const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* CONF_FILE_HPP */
