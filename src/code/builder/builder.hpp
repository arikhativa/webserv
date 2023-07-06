
#ifndef BUILDER_HPP
#define BUILDER_HPP

#include <list>
#include <string>

#include <Conf/Conf.hpp>
#include <IConfig/IConfig.hpp>
#include <Token/Token.hpp>

namespace builder
{
	IServerConf *createServer(std::list<Token>::const_iterator it, const std::list<Token>::const_iterator &end);
	IConfig *createConf(const std::string &file_name, const std::list<Token> &list);
} // namespace builder

#endif
