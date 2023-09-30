#include <arpa/inet.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
	int clientSocket;
	struct sockaddr_in serverAddr;

	// Create socket
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket < 0)
	{
		perror("Error creating socket");
		return 1;
	}

	// Set up server address
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(1234);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Connect to server
	if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
	{
		perror("Error connecting to server");
		return 1;
	}

	// Prepare HTTP request
	const char *httpRequest = "POST /upload/bin HTTP/1.1\r\n"
							  "Host: localhost\r\n"
							  "Content-Length: 20\r\n"
							  "\r\n"
							  "a\0b\0c\0d\0e\0"
							  "f\0g\0h\0i\0j\0";

	// Send HTTP request
	send(clientSocket, httpRequest, 27 + 17 + 20 + 2 + 20, 0);

	// Receive HTTP response
	char buffer[1024];
	int recvLen = recv(clientSocket, buffer, sizeof(buffer), 0);
	if (recvLen < 0)
	{
		perror("Error receiving response");
		return 1;
	}
	else if (recvLen == 0)
	{
		std::cerr << "Server closed connection" << std::endl;
		return 1;
	}
	buffer[recvLen] = '\0';

	std::cout << buffer << std::endl;

	// Close socket
	close(clientSocket);

	return 0;
}
