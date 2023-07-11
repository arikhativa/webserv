
#ifndef LISTPRINT_HPP
#define LISTPRINT_HPP

#include <iostream>
#include <list>

#include <IErrorPage/IErrorPage.hpp>

std::ostream &operator<<(std::ostream &o, const std::list<std::string> &i);
std::ostream &operator<<(std::ostream &o, const std::list<const IErrorPage *> &i);

#endif
