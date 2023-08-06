
#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <cerrno>
#include <cstdlib>
#include <limits>
#include <sstream>
#include <string>

namespace converter
{
	int stringToInt(const std::string &str);
	std::size_t stringToSizeT(const std::string &str);
	bool onOffStringToBool(const std::string &str);

	template <typename T>
	std::string numToString(T num)
	{
		std::ostringstream ss;
		ss << num;
		return ss.str();
	}

	std::string escapeString(const std::string &input);

} // namespace converter

#endif
