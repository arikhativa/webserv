
#ifndef LISTEN_HPP
#define LISTEN_HPP

#include <iostream>
#include <list>
#include <string>
#include <utility>

#include <IAddress/IAddress.hpp>
#include <IListen/IListen.hpp>
#include <IP/IP.hpp>
#include <IPort/IPort.hpp>
#include <Port/Port.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class Listen : public IListen
{
  public:
	Listen();
	Listen(const std::string &ip, const std::string &port);
	virtual ~Listen();

	virtual const IAddress &getAddress(void) const;
	virtual const IPort &getPort(void) const;

	void setAddress(const std::string &ip);
	void setPort(const std::string &port);

  private:
	static const std::string _defaultIP;
	static const uint16_t _defaultPort;

	IP _address;
	Port _port;
};

std::ostream &operator<<(std::ostream &o, Listen const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* LISTEN_HPP */
