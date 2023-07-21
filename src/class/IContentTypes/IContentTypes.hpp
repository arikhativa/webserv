#ifndef I_CONTENT_TYPES_HPP
#define I_CONTENT_TYPES_HPP

#include <list>
#include <string>
#include <iostream>
#include <map>


#ifdef TEST_ON
#define private public
#define protected public
#endif

class IContentTypes
{
  public:
	static std::map<std::string, std::string> _content_types;
	static std::map<std::string, std::string> create_map();
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_CONTENT_TYPES_HPP */
