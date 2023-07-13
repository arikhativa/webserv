
#ifndef ERROR_PAGE_HPP
#define ERROR_PAGE_HPP

#include <iostream>
#include <string>

#include <BasePairCodePath/BasePairCodePath.hpp>
#include <HTTPStatusCode/HTTPStatusCode.hpp>
#include <IErrorPage/IErrorPage.hpp>
#include <IPath/IPath.hpp>
#include <Path/Path.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class ErrorPage : public BasePairCodePath, public IErrorPage
{
  public:
	explicit ErrorPage(const std::string &status, const std::string &path);
	explicit ErrorPage(const HTTPStatusCode &status, const Path &path);
	ErrorPage(ErrorPage const &src);
	virtual ~ErrorPage();

	ErrorPage &operator=(ErrorPage const &rhs);

	virtual HTTPStatusCode getStatus(void) const;
	virtual const IPath &getPath(void) const;
};

std::ostream &operator<<(std::ostream &o, ErrorPage const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* ERROR_PAGE_HPP */
