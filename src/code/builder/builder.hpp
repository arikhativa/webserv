
#ifndef BUILDER_HPP
#define BUILDER_HPP

#include <list>

#include <Conf/Conf.hpp>
#include <IConf/IConf.hpp>
#include <IServerConf/IServerConf.hpp>
#include <ServerConf/ServerConf.hpp>
#include <Token/Token.hpp>

namespace builder
{

	const IConf *createConf(const std::string &file_name, const std::list<Token> &list);
	void creatServer(Conf &conf, std::list<Token>::const_iterator it);

	void initAllServers(Conf &conf, std::list<Token>::const_iterator &it, const std::list<Token>::const_iterator &end);

	namespace server
	{
		typedef void (*t_rule)(ServerConf &server, std::list<Token>::const_iterator it);

		t_rule get(std::list<Token>::const_iterator it);

		void serverName(ServerConf &server, std::list<Token>::const_iterator it);
		void root(ServerConf &server, std::list<Token>::const_iterator it);
		void listen(ServerConf &server, std::list<Token>::const_iterator it);
		void index(ServerConf &server, std::list<Token>::const_iterator it);
		void errorPage(ServerConf &server, std::list<Token>::const_iterator it);
		void redirect(ServerConf &server, std::list<Token>::const_iterator it);
		void clientMaxBodySize(ServerConf &server, std::list<Token>::const_iterator it);
		void location(ServerConf &server, std::list<Token>::const_iterator it);

	} // namespace server

	namespace location
	{
		typedef void (*t_rule)(Location &location, std::list<Token>::const_iterator it);

		t_rule get(std::list<Token>::const_iterator it);

		void path(Location &location, std::list<Token>::const_iterator it);
		void autoIndex(Location &location, std::list<Token>::const_iterator it);
		void upload(Location &location, std::list<Token>::const_iterator it);
		void maxBodySize(Location &location, std::list<Token>::const_iterator it);
		void allowedMethods(Location &location, std::list<Token>::const_iterator it);
		void redirect(Location &location, std::list<Token>::const_iterator it);
		void indexFiles(Location &location, std::list<Token>::const_iterator it);
		void errorPage(Location &location, std::list<Token>::const_iterator it);
		void root(Location &location, std::list<Token>::const_iterator it);

	} // namespace location

} // namespace builder

#endif
