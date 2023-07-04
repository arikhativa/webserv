
#ifndef I_INDEX_FILES_HPP
#define I_INDEX_FILES_HPP

#include <iostream>
#include <string>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class IIndexFiles
{
  public:
	virtual ~IIndexFiles() = default;
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_INDEX_FILES_HPP */
