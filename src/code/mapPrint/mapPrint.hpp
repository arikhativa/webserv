
#ifndef MAPPRINT_HPP
#define MAPPRINT_HPP

#include <iostream>
#include <map>

#include <HTTPStatusCode/HTTPStatusCode.hpp>
#include <converter/converter.hpp>

std::ostream &operator<<(std::ostream &o, const std::map<std::string, std::string> &i);
std::ostream &operator<<(std::ostream &o, const std::map<HTTPStatusCode::Code, std::string> &i);

#endif
