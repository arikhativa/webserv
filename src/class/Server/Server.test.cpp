
#include <Server/Server.hpp>
#include <gtest/gtest.h>

#include <Conf/Conf.hpp>
#include <FileManager/FileManager.hpp>
#include <builder/builder.hpp>
#include <lexer/lexer.hpp>
#include <parser/parser.hpp>

static const IConf *createConf(const std::string &path)
{
	const IConf *conf;
	std::fstream fs(path.c_str());
	if (!FileManager::isOpen(fs))
	{
		std::cerr << "Error: failed to open file: " << path << std::endl;
		return NULL;
	}

	std::list<Token> list(lexer::tokenize(fs));
	if (!parser::validate(list))
	{
		std::cerr << "Error: bad syntax in config file: " << path << std::endl;
		fs.close();
		return NULL;
	}

	try
	{
		conf = builder::createConf(path, list);
		builder::validate(conf);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: invalid config file: " << path << ": " << e.what() << std::endl;
		fs.close();
		return NULL;
	}
	fs.close();

	return conf;
}

TEST(Server, CreateDestroy)
{
	Conf conf("file");
	conf.addDefaultServerIfNeeded();

	std::list<const IServerConf *> servers = conf->getServers();
	obj = new Server(*(servers.begin()));
	delete obj;
}

TEST(Server, AcceptingConnectionFailed)
{
	Conf conf("file");
	conf.addDefaultServerIfNeeded();

	std::list<const IServerConf *> servers = conf->getServers();
	obj = new Server(*(servers.begin()));
	EXPECT_THROW(obj->acceptConnection(-1), Server::AcceptingConnectionFailed);
	delete obj;
}