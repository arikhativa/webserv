
#ifndef ERROR_PAGE_HPP
#define ERROR_PAGE_HPP

#include <iostream>
#include <string>

#include <HTTPStatusCode/HTTPStatusCode.hpp>
#include <IErrorPage/IErrorPage.hpp>
#include <IPath/IPath.hpp>
#include <Path/Path.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class ErrorPage : public IErrorPage
{
  public:
	explicit ErrorPage(const std::string &status, const std::string &path);
	explicit ErrorPage(const HTTPStatusCode &status, const Path &path);
	ErrorPage(ErrorPage const &src);
	virtual ~ErrorPage();

	ErrorPage &operator=(ErrorPage const &rhs);

	virtual HTTPStatusCode getStatus(void) const;
	virtual const IPath &getPath(void) const;

	void setStatus(HTTPStatusCode status);
	void setPath(const Path &path);
	void setStatus(const std::string &status);
	void setPath(const std::string &path);

  private:
	HTTPStatusCode _status;
	Path _path;
};

std::ostream &operator<<(std::ostream &o, ErrorPage const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* ERROR_PAGE_HPP */
