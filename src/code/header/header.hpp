
#ifndef HEADER_HPP
#define HEADER_HPP

#include <httpConstants/httpConstants.hpp>
#include <iostream>
#include <string>

namespace header
{
	bool validateHeaders(const std::string &headers);
	bool isHeaderLineValid(const std::string &headers);

} // namespace header

#endif
