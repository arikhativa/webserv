
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
	Path(const Path &src);
	virtual ~Path();

	Path &operator=(const Path &rhs);

	const std::string &get(void) const;
	void set(const std::string &path);
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
