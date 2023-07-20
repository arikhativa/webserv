/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: al7aro <al7aro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:25:39 by yrabby            #+#    #+#             */
/*   Updated: 2023/07/10 18:01:51 by al7aro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main/main.hpp>

#include <ServerManager/ServerManager.hpp>
#include <IP/IP.hpp>
#include <Port/Port.hpp>
#include <Socket/Socket.hpp>
#include <csignal>

ServerManager sm;

void signalHandler( int signum )
{
	sm.close();
	std::cout << "Server succesfully closed." << std::endl;
	exit(signum);
}

int main(void)
{
	try
	{
		signal(SIGINT, signalHandler);

		sm.setup();
		sm.start();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << "main!!" << '\n';
		ILogger::consoleLogError(e.what());
	}
	return 0;
}