
#ifndef TAB_HPP
#define TAB_HPP

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <string>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class Tab
{
  public:
	Tab();
	~Tab();

	class TabException : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

	void add(const std::string &value);
	const std::string &get(const int &key) const;
	char **toCTable(void) const;
	void freeTab(char **tab) const;

  private:
	std::map<int, std::string> _tab;
};

std::ostream &operator<<(std::ostream &o, const Tab &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* TAB_HPP */
