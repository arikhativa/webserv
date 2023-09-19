
#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <cerrno>
#include <cstdlib>
#include <limits>
#include <map>
#include <sstream>
#include <string>

#include <httpConstants/httpConstants.hpp>

namespace converter
{
	int stringToInt(const std::string &str);
	std::size_t stringToSizeT(const std::string &str);
	bool onOffStringToBool(const std::string &str);
	size_t hexStringToSizeT(const std::string &hexStr);
	std::string urlDecode(const std::string &url);

	template <typename T>
	std::string numToString(T num)
	{
		std::ostringstream ss;
		ss << num;
		return ss.str();
	}

	std::string escapeString(const std::string &input);
	std::string toNginxStyle(const std::string &input);
	std::string headersToString(std::map<std::string, std::string> map);
	std::string removeQuotesIfNeeded(std::string &str);

} // namespace converter

#endif
