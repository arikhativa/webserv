
#ifndef I_C_G_I_LOCATION_HPP
#define I_C_G_I_LOCATION_HPP

#include <iostream>
#include <string>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class ICGILocation
{
  public:
	virtual ~ICGILocation(){};
	virtual IPath getPath(void) const = 0;
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_C_G_I_LOCATION_HPP */
