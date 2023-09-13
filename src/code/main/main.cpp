/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alopez-g <alopez-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:25:39 by yrabby            #+#    #+#             */
/*   Updated: 2023/08/30 10:15:28 by alopez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main/main.hpp>

static bool isInputValid(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Usage: ./webserv [config_file]" << std::endl;
		return false;
	}
	if (FileManager::isDirectory(av[1]))
	{
		std::cerr << "Error: " << av[1] << " is a directory" << std::endl;
		return false;
	}
	if (!FileManager::isFileExists(av[1]))
	{
		std::cerr << "Error: " << av[1] << " does not exist" << std::endl;
		return false;
	}
	return true;
}

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

int main(int ac, char **av)
{
	if (!isInputValid(ac, av))
		return EXIT_FAILURE;

	const IConf *conf(createConf(av[1]));
	if (!conf)
		return EXIT_FAILURE;

	ServerManager sm(conf);
	sm.setup();
	sm.start();
	sm.terminate();

	delete conf;
	return EXIT_SUCCESS;
}
