
#ifndef I_STATUS_CODES_HPP
#define I_STATUS_CODES_HPP

#include <list>
#include <string>
#include <iostream>
#include <map>


#ifdef TEST_ON
#define private public
#define protected public
#endif

class IStatusCodes
{
	public :
		static std::map<int, std::string> _status_codes;
		static std::map<int, std::string> create_map();
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_STATUS_CODES_HPP */
