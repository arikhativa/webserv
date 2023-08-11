#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>

int main()
{
	int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == -1)
	{
		perror("socket");
		return EXIT_FAILURE;
	}

	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(12345);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
	{
		perror("connect");
		return EXIT_FAILURE;
	}

	// Set non-blocking mode for the client socket
	int flags = fcntl(clientSocket, F_GETFL, 0);
	fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK);

	{
		const char *str = "01234567891";
		send(clientSocket, str, strlen(str), 0);
		sleep(1);
	}
	{

		const char *str = "hey2";
		send(clientSocket, str, strlen(str), 0);
		sleep(1);
	}
	{
		const char *str = "EOF";
		send(clientSocket, str, strlen(str), 0);
		sleep(1);
	}

	close(clientSocket);
	return 0;
}
