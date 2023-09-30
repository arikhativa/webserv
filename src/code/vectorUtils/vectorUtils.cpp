
#include <vectorUtils/vectorUtils.hpp>

::size_t vectorUtils::find(const std::vector< char > &buff, const std::vector< char > &find, ::size_t start)
{
	for (size_t i = start; i <= buff.size() - find.size(); ++i)
	{
		bool found = true;
		for (size_t j = 0; j < find.size(); ++j)
		{
			if (buff[i + j] != find[j])
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			return i;
		}
	}
	return std::string::npos;
}

static std::string toLowerCase(const std::string &str)
{
	std::string result = str;
	for (size_t i = 0; i < result.length(); ++i)
	{
		result[i] = std::tolower(result[i]);
	}
	return result;
}

::size_t vectorUtils::findCaseInsensitive(const std::vector< char > &vec, const std::string &search)
{
	std::string search_lower = toLowerCase(search);

	for (size_t i = 0; i < vec.size(); ++i)
	{
		char ch = std::tolower(vec[i]);
		if (ch == search_lower[0])
		{
			bool found = true;
			for (size_t j = 1; j < search_lower.size(); ++j)
			{
				if (i + j >= vec.size() || std::tolower(vec[i + j]) != search_lower[j])
				{
					found = false;
					break;
				}
			}
			if (found)
			{
				return i;
			}
		}
	}

	return std::string::npos;
}

std::vector< char > vectorUtils::subvec(const std::vector< char > &vec, size_t start, size_t length)
{
	if (start >= vec.size())
	{
		return std::vector< char >();
	}

	size_t end = start + length;
	if (end > vec.size())
	{
		end = vec.size();
	}
	if (0 == length)
	{
		end = vec.size();
	}

	return std::vector< char >(vec.begin() + start, vec.begin() + end);
}
