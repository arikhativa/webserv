
#ifndef ALLOWED_METHODS_HPP
#define ALLOWED_METHODS_HPP

#include <iostream>
#include <list>
#include <string>

#include <IAllowedMethods/IAllowedMethods.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class AllowedMethods : public IAllowedMethods
{
  public:
	static const std::string GET;
	static const std::string POST;
	static const std::string DELETE;

	AllowedMethods();
	explicit AllowedMethods(const std::list<std::string> &methods);
	AllowedMethods(AllowedMethods const &src);
	virtual ~AllowedMethods();

	AllowedMethods &operator=(AllowedMethods const &rhs);

	virtual bool isAllowed(IAllowedMethods::type method) const;

	bool getGET(void) const;
	bool getPOST(void) const;
	bool getDELETE(void) const;
	void setGET(bool b);
	void setPOST(bool b);
	void setDELETE(bool b);

	class InvalidMethodException : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

  private:
	bool _get;
	bool _post;
	bool _delete;
};

std::ostream &operator<<(std::ostream &o, AllowedMethods const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* ALLOWED_METHODS_HPP */
