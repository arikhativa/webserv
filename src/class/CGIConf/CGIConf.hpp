
#ifndef C_G_I_CONF_HPP
#define C_G_I_CONF_HPP

#include <iostream>
#include <string>

#include <Path/Path.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class CGIConf
{
  public:
	CGIConf();
	CGIConf(const CGIConf &src);
	~CGIConf();

	class InvalidExtension : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

	CGIConf &operator=(const CGIConf &rhs);

	static bool isValidExtension(const std::string &str);

	void setExtension(const std::string &ext);
	void setPath(const std::string &path);

	bool isSet(void) const;

	std::string getExtension(void) const;
	const Path &getPath(void) const;

  private:
	static const std::string _PYTHON;
	static const std::string _PHP;

	std::string _extension;
	Path _path;
};

std::ostream &operator<<(std::ostream &o, const CGIConf &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* C_G_I_CONF_HPP */
