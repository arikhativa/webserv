
#ifndef PATH_HPP
#define PATH_HPP

#include <iostream>
#include <string>

#include <IPath/IPath.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class Path : public IPath
{
  public:
	Path();
	explicit Path(const std::string &path);
	Path(Path const &src);
	virtual ~Path();

	Path &operator=(Path const &rhs);

	const std::string &getPath(void) const;
	void setPath(const std::string &path);
	bool isRelative(void);
	bool isAbsolute(void);

  private:
	std::string _path;
};

std::ostream &operator<<(std::ostream &o, Path const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* PATH_HPP */
