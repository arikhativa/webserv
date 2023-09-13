
#ifndef ERROR_PAGE_SET_HPP
#define ERROR_PAGE_SET_HPP

#include <iostream>
#include <string>

#include <Path/Path.hpp>
#include <defaultPager/defaultPager.hpp>
#include <mapPrint/mapPrint.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class ErrorPageSet
{
  public:
	ErrorPageSet();
	ErrorPageSet(const ErrorPageSet &src);
	~ErrorPageSet();

	void setPage(HTTPStatusCode::Code code, const std::string &page);
	void setRoot(const Path &root);

	std::string getPage(HTTPStatusCode::Code code) const;
	const std::map<HTTPStatusCode::Code, std::string> &getPages(void) const;

	ErrorPageSet &operator=(const ErrorPageSet &rhs);

  private:
	Path _root;
	std::map<HTTPStatusCode::Code, std::string> _pages;
};

std::ostream &operator<<(std::ostream &o, const ErrorPageSet &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* ERROR_PAGE_SET_HPP */
