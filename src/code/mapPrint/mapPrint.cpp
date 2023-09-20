
#include <mapPrint/mapPrint.hpp>

std::ostream &operator<<(std::ostream &o, const std::map< std::string, std::string > &i)
{
	o << "{";
	for (std::map< std::string, std::string >::const_iterator it = i.begin(); it != i.end(); it++)
	{
		o << "\"" << it->first << "\": "
		  << "\"" << converter::escapeString(it->second) << "\"";
		if (it != --i.end())
			o << ", ";
	}
	o << "}";
	return o;
}

std::ostream &operator<<(std::ostream &o, const std::map< HTTPStatusCode::Code, std::string > &i)
{
	o << "{";
	for (std::map< HTTPStatusCode::Code, std::string >::const_iterator it = i.begin(); it != i.end(); it++)
	{
		o << "\"" << it->first << "\": "
		  << "\"" << converter::escapeString(it->second) << "\"";
		if (it != --i.end())
			o << ", ";
	}
	o << "}";
	return o;
}
