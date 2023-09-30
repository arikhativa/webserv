
#ifndef VECTORUTILS_HPP
#define VECTORUTILS_HPP

#include <string>
#include <vector>

namespace vectorUtils
{
	::size_t find(const std::vector< char > &buff, const std::vector< char > &find, ::size_t start = 0);
	::size_t findCaseInsensitive(const std::vector< char > &vec, const std::string &search);
	std::vector< char > subvec(const std::vector< char > &vec, size_t start, size_t length);

} // namespace vectorUtils

#endif
