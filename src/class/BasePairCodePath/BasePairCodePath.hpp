
#ifndef BASE_PAIR_CODE_PATH_HPP
#define BASE_PAIR_CODE_PATH_HPP

#include <iostream>
#include <string>

#include <HTTPStatusCode/HTTPStatusCode.hpp>
#include <IPath/IPath.hpp>
#include <Path/Path.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class BasePairCodePath
{
  public:
	explicit BasePairCodePath(const std::string &status, const std::string &path);
	explicit BasePairCodePath(const HTTPStatusCode &status, const Path &path);
	BasePairCodePath(const BasePairCodePath &src);
	virtual ~BasePairCodePath();

	BasePairCodePath &operator=(const BasePairCodePath &rhs);

	HTTPStatusCode getStatus(void) const;
	const IPath &getPath(void) const;

	class InvalidPathException : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

  protected:
	void setStatus(HTTPStatusCode status);
	void setPath(const Path &path);
	void setStatus(const std::string &status);
	void setPath(const std::string &path);

  private:
	HTTPStatusCode _status;
	Path _path;
};

std::ostream &operator<<(std::ostream &o, const BasePairCodePath &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* BASE_PAIR_CODE_PATH_HPP */
