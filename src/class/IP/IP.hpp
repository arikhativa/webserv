
#ifndef I_P_HPP
#define I_P_HPP

#include <IAddress/IAddress.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class IP : public IAddress
{
  public:
	explicit IP(const std::string &ip);
	IP(IP const &src);
	virtual ~IP();

	IP &operator=(IP const &rhs);

	virtual std::string get(void) const;
	void setAddress(const std::string &address);

	static bool isValid(const std::string &ip);

	class InvalidIPException : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

  private:
	std::string _ip;
};

std::ostream &operator<<(std::ostream &o, IP const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_P_HPP */
