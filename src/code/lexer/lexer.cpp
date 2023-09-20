
#include <lexer/lexer.hpp>

static void addTokens(std::list< Token > &list, std::string &line)
{
	std::size_t i = 0;
	std::size_t start = 0;

	while (line[i])
	{
		while (std::isspace(line[i]))
			++i;
		start = i;
		while (line[i] && !Token::isSpecialChar(line[i]) && !std::isspace(line[i]))
			++i;
		if (i == start)
		{
			if (Token::isSpecialChar(line[i]))
			{
				list.push_back(Token(line.substr(i, 1)));
				++i;
			}
		}
		else
			list.push_back(Token(line.substr(start, i - start)));
	}
}

std::list< Token > lexer::tokenize(std::fstream &fs)
{
	std::list< Token > list;
	std::string line;

	while (std::getline(fs, line))
		addTokens(list, line);
	return list;
}
