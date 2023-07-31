
#include <listPrint/listPrint.hpp>

std::ostream &operator<<(std::ostream &o, const std::list<std::string> &i)
{
	o << "[";
	for (std::list<std::string>::const_iterator it = i.begin(); it != i.end(); it++)
	{
		o << "\"" << *it << "\"";
		if (it != --i.end())
			o << ", ";
	}
	o << "]";
	return o;
}

std::ostream &operator<<(std::ostream &o, const std::list<const IErrorPage *> &i)
{
	o << "[";
	for (std::list<const IErrorPage *>::const_iterator it = i.begin(); it != i.end(); it++)
	{
		o << **it;
		if (it != --i.end())
			o << ", ";
	}
	o << "]";
	return o;
}
