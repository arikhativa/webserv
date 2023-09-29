
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
	if (errno == ERANGE || longValue > std::numeric_limits< long long >::max() ||
		longValue < std::numeric_limits< long long >::min())
	{
		throw std::out_of_range("Overflow: " + str);
	}

	result = static_cast< std::size_t >(longValue);
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

static bool isValidLong(const std::string &str)
{
	if (str.empty())
		return false;
	size_t i = 0;
	if (str[0] == '-')
		i++;
	while (i < str.length())
	{
		if (!isdigit(str[i]))
			return false;
		i++;
	}
	return true;
}

int converter::stringToInt(const std::string &str)
{
	if (!isValidLong(str))
		throw std::invalid_argument("Invalid input: " + str);

	const char *charStr = str.c_str();

	char *endPtr;
	errno = 0;
	int ret;

	long long longValue = std::strtoll(charStr, &endPtr, 10);
	if (errno == ERANGE || longValue > std::numeric_limits< int >::max() ||
		longValue < std::numeric_limits< int >::min())
	{
		throw std::out_of_range("Overflow: " + str);
	}

	ret = static_cast< int >(longValue);
	return ret;
}

size_t converter::hexStringToSizeT(const std::string &hexStr)
{
	size_t result = 0;
	std::stringstream ss;
	ss << std::hex << hexStr;
	ss >> result;
	return (result);
}

std::string converter::vectorToString(std::vector< char > vec)
{
	std::string result(vec.begin(), vec.end());
	return result;
}

std::string converter::escapeString(const std::string &input)
{
	std::string escapedString;
	for (size_t i = 0; i < input.length(); i++)
	{
		switch (input[i])
		{
		case '\"':
			escapedString += "\\\"";
			break;
		case '\'':
			escapedString += "\\\'";
			break;
		case '\\':
			escapedString += "\\\\";
			break;
		case '\n':
			escapedString += "\\n";
			break;
		case '\r':
			escapedString += "\\r";
			break;
		case '\t':
			escapedString += "\\t";
			break;
		default:
			escapedString += input[i];
			break;
		}
	}
	return escapedString;
}

std::string converter::toNginxStyle(const std::string &input)
{
	std::string result;
	char c = 0;
	int i = 0;
	bool capitalizeNext = true;

	while (input[i])
	{
		c = input[i];
		if (std::isalpha(c))
		{
			if (capitalizeNext)
			{
				result += static_cast< char >(std::toupper(c));
				capitalizeNext = false;
			}
			else
				result += static_cast< char >(std::tolower(c));
		}
		else if (c == ' ' || c == '-')
		{
			capitalizeNext = true;
			result += '-';
		}
		else
			result += c;
		++i;
	}
	return result;
}

std::string converter::headersToString(std::map< std::string, std::string > map)
{
	std::string result;

	for (std::map< std::string, std::string >::iterator it = map.begin(); it != map.end(); ++it)
	{
		result += it->first + ": " + it->second + httpConstants::FIELD_BREAK;
	}
	return result + httpConstants::FIELD_BREAK;
}

std::string converter::removeQuotesIfNeeded(std::string &str)
{
	if (str.length() >= 2 && str[0] == '"' && str[str.length() - 1] == '"')
		return str.substr(1, str.length() - 2);
	return str;
}

std::string converter::urlDecode(const std::string &url)
{
	std::string result;
	char c;
	int i = 0;

	while (url[i])
	{
		c = url[i];
		if (c == '%')
		{
			if (url[i + 1] && url[i + 2])
			{
				result += static_cast< char >(converter::hexStringToSizeT(url.substr(i + 1, 2)));
				i += 2;
			}
			else
				return url;
		}
		else if (c == '+')
			result += ' ';
		else
			result += c;
		++i;
	}
	return result;
}

void converter::mergeSpaces(std::string &str)
{
	bool inSpace = false;
	size_t j = 0;

	for (size_t i = 0; i < str.size(); ++i)
	{
		if (std::isspace(static_cast< unsigned char >(str[i])))
		{
			if (!inSpace)
			{
				str[j++] = ' ';
				inSpace = true;
			}
		}
		else
		{
			str[j++] = str[i];
			inSpace = false;
		}
	}

	if (j > 0 && std::isspace(static_cast< unsigned char >(str[j - 1])))
	{
		str.resize(j - 1);
	}
	else
	{
		str.resize(j);
	}
}

std::string converter::HTTPResponseSimplified(const std::string &http_response)
{
	std::string ret;
	size_t start;
	size_t end;

	start = http_response.find(" ");
	if (start == std::string::npos)
		return "";
	end = http_response.find("\r");
	if (start != std::string::npos && end != std::string::npos)
		ret = http_response.substr(start + 1, end - start - 1);
	return ret;
}
