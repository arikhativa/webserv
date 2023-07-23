/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrabby <yrabby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:25:39 by yrabby            #+#    #+#             */
/*   Updated: 2023/06/28 13:30:37 by yrabby           ###   ########.fr       */
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
	signal(SIGINT, signalHandler);

	sm.setup();
	sm.start();
	return 0;
}