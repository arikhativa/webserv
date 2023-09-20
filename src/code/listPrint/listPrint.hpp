
#ifndef LISTPRINT_HPP
#define LISTPRINT_HPP

#include <iostream>
#include <list>

#include <IErrorPage/IErrorPage.hpp>
#include <IListen/IListen.hpp>
#include <ILocation/ILocation.hpp>
#include <IServerConf/IServerConf.hpp>

std::ostream &operator<<(std::ostream &o, const std::list< std::string > &i);
std::ostream &operator<<(std::ostream &o, const std::list< const IListen * > &i);
std::ostream &operator<<(std::ostream &o, const std::list< const IErrorPage * > &i);
std::ostream &operator<<(std::ostream &o, const std::list< const ILocation * > &i);
std::ostream &operator<<(std::ostream &o, const std::list< const IServerConf * > &i);

#endif
