#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <poll.h>
#include <string>
#include <unistd.h>
#include <vector>

bool rrr(int clientSocket)
{
	char buffer[10];
	int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

	if (bytesReceived > 0)
	{
		if (bytesReceived == 10)
		{
			std::cout << "MAX msg: " << std::endl;
		}
		buffer[bytesReceived] = '\0';
		std::cout << "Received: " << buffer << std::endl;
	}
	else if (bytesReceived == 0)
	{
		std::cout << "Connection closed by the client" << std::endl;
		close(clientSocket);
		return true;
	}
	else
	{
		perror("recv");
	}
	return false;
}

int main()
{

	// // Set up pipes for CGI communication
	// int toCgiPipe[2];
	// int fromCgiPipe[2];
	// pipe(toCgiPipe);
	// pipe(fromCgiPipe);

	// // Fork and execute a CGI program
	// pid_t childPID = fork();
	// if (childPID == 0)
	// {
	// 	// Child process (CGI program)
	// 	close(toCgiPipe[1]);
	// 	close(fromCgiPipe[0]);
	// 	dup2(toCgiPipe[0], STDIN_FILENO);
	// 	dup2(fromCgiPipe[1], STDOUT_FILENO);
	// 	char **argv = new char *[3];
	// 	argv[0] = "/usr/bin/python3";
	// 	argv[1] = "/home/yoav/webserv/script.py";
	// 	argv[2] = NULL;

	// 	char **end = new char *[1];
	// 	argv[0] = NULL;

	// 	execve(argv[0], argv, end);
	// 	perror("execve");
	// 	exit(EXIT_FAILURE);
	// }

	// // Parent process
	// close(toCgiPipe[0]);
	// close(fromCgiPipe[1]);

	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1)
	{
		perror("socket");
		return EXIT_FAILURE;
	}

	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(12345);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
	{
		perror("bind");
		return EXIT_FAILURE;
	}

	if (listen(serverSocket, 5) == -1)
	{
		perror("listen");
		return EXIT_FAILURE;
	}

	std::cout << "Server listening on port 12345..." << std::endl;

	// Set non-blocking mode
	int flags = fcntl(serverSocket, F_GETFL, 0);
	fcntl(serverSocket, F_SETFL, flags | O_NONBLOCK);

	std::vector<pollfd> pollfds;
	pollfds.push_back({serverSocket, POLLIN});
	// pollfds.push_back({toCgiPipe[1], POLLOUT});
	// pollfds.push_back({fromCgiPipe[0], POLLIN});

	while (true)
	{
		int pollResult = poll(pollfds.data(), pollfds.size(), -1);

		if (pollResult == -1)
		{
			perror("poll");
			break;
		}

		if (pollResult > 0)
		{
			for (size_t i = 0; i < pollfds.size(); ++i)
			{
				if (pollfds[i].revents & POLLIN)
				{
					if (pollfds[i].fd == serverSocket)
					{
						// New client connection
						int clientSocket = accept(serverSocket, NULL, NULL);
						if (clientSocket > 0)
						{
							std::cout << "Client connected" << std::endl;

							// Set non-blocking mode for the client socket
							flags = fcntl(clientSocket, F_GETFL, 0);
							fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK);

							pollfds.push_back({clientSocket, POLLIN}); // Add client socket to the array
						}
					}
					else
					{
						if (rrr(pollfds[i].fd))
						{
							close(pollfds[i].fd);
							pollfds.erase(pollfds.begin() + i); // Remove client socket from the array
							--i;
							std::cout << "Client disconnected" << std::endl;
							break;
						}
					}
				}
			}
		}
	}
	// close(toCgiPipe[1]);
	// close(fromCgiPipe[0]);
	close(serverSocket);
	std::cout << "Sever disconnected" << std::endl;
	return 0;
}
