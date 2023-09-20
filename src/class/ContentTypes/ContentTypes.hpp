#ifndef CONTENT_TYPES_HPP
#define CONTENT_TYPES_HPP

#include <iostream>
#include <list>
#include <map>
#include <string>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class ContentTypes
{
  public:
	explicit ContentTypes(std::string content_type);
	ContentTypes &operator=(const ContentTypes &rhs);
	~ContentTypes();

	class InvalidExtensionException : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

	std::string get(void) const;
	static bool isValid(std::string content_type);

  private:
	static const std::map< std::string, std::string > _content_types;
	std::string _content_type;
};

std::ostream &operator<<(std::ostream &o, ContentTypes const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* CONTENT_TYPES_HPP */
