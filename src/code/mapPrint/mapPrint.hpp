
#ifndef MAPPRINT_HPP
#define MAPPRINT_HPP

#include <iostream>
#include <map>

#include <converter/converter.hpp>

std::ostream &operator<<(std::ostream &o, const std::map<std::string, std::string> &i);

#endif
