
#ifndef I_ALLOWED_METHODS_HPP
#define I_ALLOWED_METHODS_HPP

#include <list>
#include <string>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class IAllowedMethods
{
  public:
	enum type
	{
		GET,
		POST,
		DELETE,
	};

	virtual ~IAllowedMethods(){};
	virtual bool isAllowed(type method) const = 0;
};

std::ostream &operator<<(std::ostream &o, const IAllowedMethods &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_ALLOWED_METHODS_HPP */
