
#ifndef PARSER_HPP
#define PARSER_HPP

#include <list>
#include <map>
#include <string>

#include <Token/Token.hpp>

namespace parser
{

typedef bool (*t_rule)(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end);

t_rule getRule(std::list<Token>::const_iterator it);

// rules
bool serverRule(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end);
bool autoIndexRule(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end);

// is
bool isValidServerKeyword(const std::list<Token>::const_iterator &it);

bool validate(const std::list<Token> &list);

} // namespace parser

#endif