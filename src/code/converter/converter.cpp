
#include <converter/converter.hpp>

static bool isValidSizeT(const std::string &str)
{
	if (str.empty())
		return false;
	for (size_t i = 0; i < str.length(); ++i)
	{
		if (!isdigit(str[i]))
			return false;
	}
	return true;
}

std::size_t converter::stringToSizeT(const std::string &str)
{
	if (!isValidSizeT(str))
		throw std::invalid_argument("Invalid input: " + str);

	const char *charStr = str.c_str();

	std::size_t result;
	char *endPtr;
	errno = 0;

	long long longValue = std::strtoll(charStr, &endPtr, 10);
	if (errno == ERANGE || longValue > std::numeric_limits<long long>::max() ||
		longValue < std::numeric_limits<long long>::min())
	{
		throw std::out_of_range("Overflow: " + str);
	}

	result = static_cast<std::size_t>(longValue);
	return result;
}

bool converter::onOffStringToBool(const std::string &str)
{
	if (str == "on")
		return true;
	else if (str == "off")
		return false;
	else
		throw std::invalid_argument("Invalid input: " + str);
}
