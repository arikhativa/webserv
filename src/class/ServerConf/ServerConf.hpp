
#ifndef SERVER_CONF_HPP
#define SERVER_CONF_HPP

#include <iostream>
#include <string>

#include <ErrorPage/ErrorPage.hpp>
#include <IListen/IListen.hpp>
#include <IServerConf/IServerConf.hpp>
#include <Listen/Listen.hpp>
#include <Location/Location.hpp>
#include <OnOff/OnOff.hpp>
#include <Path/Path.hpp>
#include <Return/Return.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class ServerConf : public IServerConf
{
  public:
	static const std::string DEFAULT_ROOT;
	static const std::string DEFAULT_SERVER_NAME;
	static const std::string DEFAULT_HTM;
	static const std::string DEFAULT_HTML;

	ServerConf();
	virtual ~ServerConf();

	virtual std::string getName(void) const;
	virtual std::size_t getMaxBodySize(void) const;
	virtual const IReturn *getReturn(void) const;
	virtual const IPath *getRoot(void) const;
	virtual const std::list<std::string> &getIndexFiles(void) const;
	virtual std::list<const IErrorPage *> getErrorPages(void) const;
	virtual std::list<const IListen *> getListen(void) const;
	virtual std::list<const ILocation *> getLocations(void) const;

	void setDefaultSettingIfNeeded(void);
	void setName(const std::string &name);
	void setMaxBodySize(const std::string &size);
	void setReturn(const std::string &status, const std::string &path);
	void setRoot(const std::string &path);
	void setIndexFiles(const std::list<std::string> &index_files);
	void addErrorPage(const std::string &status, const std::string &path);
	void addListenByPort(const std::string &port);
	void addListenByIP(const std::string &ip);
	void addListen(const std::string &ip, const std::string &port);
	void addListen(const Listen &listen);

	Location &createGetLocation(void);

	class InvalidServerConf : public std::exception
	{
	  public:
		explicit InvalidServerConf(const std::string &msg);
		virtual ~InvalidServerConf() throw();
		virtual const char *what() const throw();

	  private:
		std::string _msg;
	};

  private:
	OnOff<std::string> _name;
	OnOff<std::size_t> _max_body_size;
	Return *_return;
	Path *_root;
	std::list<std::string> _index_files;
	std::list<ErrorPage> _error_pages;
	std::list<Listen> _listen;
	std::list<Location> _locations;
};

std::ostream &operator<<(std::ostream &o, ServerConf const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* SERVER_CONF_HPP */
