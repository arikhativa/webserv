
#include <parser/parser.hpp>

static std::map<std::string, bool> initServerValidKeywords(void)
{
	std::map<std::string, bool> map;

	map["server_name"] = true;
	map["root"] = true;
	map["listen"] = true;
	map["index"] = true;
	map["error_page"] = true;
	map["return"] = true;
	map["client_max_body_size"] = true;
	map["location"] = true;

	return map;
}

static std::map<std::string, bool> initLocationValidKeywords(void)
{
	std::map<std::string, bool> map;

	map["allow_methods"] = true;
	map["client_max_body_size"] = true;
	map["root"] = true;
	map["index"] = true;
	map["return"] = true;
	map["autoindex"] = true;
	map["upload"] = true;

	return map;
}

bool parser::isValidServerKeyword(const std::list<Token>::const_iterator &it)
{
	static const std::map<std::string, bool> valid_keywords(initServerValidKeywords());
	try
	{
		return valid_keywords.at(it->getValue());
	}
	catch (...)
	{
		return false;
	}
}

bool parser::isValidLocationKeyword(const std::list<Token>::const_iterator &it)
{
	static const std::map<std::string, bool> valid_keywords(initLocationValidKeywords());
	try
	{
		return valid_keywords.at(it->getValue());
	}
	catch (...)
	{
		return false;
	}
}

// TODO think about "server"
bool parser::validate(const std::list<Token> &list)
{
	parser::t_rule f;
	std::list<Token>::const_iterator it = list.begin();

	if (list.empty())
		return false;
	if (it->getValue() != "server")
		return false;
	while (it != list.end())
	{
		if (it->getValue() == "server")
		{
			f = parser::rule::get(it);
			if (!f(it, list.end()))
				return false;
		}
		++it;
	}
	return true;
}
