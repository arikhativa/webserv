
#include <header/header.hpp>

bool header::isHeaderLineValid(const std::string &headers)
{
	::size_t pos = headers.find(":");
	if (pos == std::string::npos || pos == 0)
		return false;

	::size_t tmp = headers.find(":", pos + 1);
	if (tmp != std::string::npos)
		return false;

	++pos;
	if (headers[pos] == '\r')
		return false;

	while (headers[pos] == ' ')
		++pos;

	if (pos == headers.size())
		return false;

	return true;
}

bool header::validateHeaders(const std::string &headers)
{
	::size_t last = headers.find(httpConstants::HEADER_BREAK);
	if (last == std::string::npos)
	{
		return false;
	}

	::size_t pos = 0;
	::size_t end = headers.find(httpConstants::FIELD_BREAK);

	while (pos < last && end != last)
	{
		if (!isHeaderLineValid(headers.substr(pos, end - pos)))
			return false;
		pos = end + httpConstants::FIELD_BREAK.length();
		end = headers.find(httpConstants::FIELD_BREAK, pos);
	}

	return true;
}
