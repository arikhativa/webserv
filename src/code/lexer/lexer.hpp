
#ifndef LEXER_HPP
#define LEXER_HPP

#include <fstream>
#include <list>
#include <string>

#include <Token/Token.hpp>

namespace lexer
{
std::list<Token> tokenize(std::fstream &fs);
}

#endif
