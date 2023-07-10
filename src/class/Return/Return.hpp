
#ifndef RETURN_HPP
#define RETURN_HPP

#include <iostream>
#include <string>

#include <BasePairCodePath/BasePairCodePath.hpp>
#include <HTTPStatusCode/HTTPStatusCode.hpp>
#include <IPath/IPath.hpp>
#include <IReturn/IReturn.hpp>
#include <Path/Path.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class Return : public BasePairCodePath, public IReturn
{
  public:
	explicit Return(const std::string &status, const std::string &path);
	explicit Return(const HTTPStatusCode &status, const Path &path);
	Return(Return const &src);
	virtual ~Return();

	Return &operator=(Return const &rhs);

	virtual HTTPStatusCode getStatus(void) const;
	virtual const IPath &getPath(void) const;
};

std::ostream &operator<<(std::ostream &o, Return const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* RETURN_HPP */
