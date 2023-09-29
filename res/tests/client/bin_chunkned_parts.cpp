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
							  "Transfer-Encoding: chunked\r\n"
							  "\r\n"
							  "5\r\n"
							  "f\0g\0h\r\n"
							  "4\r\n"
							  "\0aa\0\r\n";

	const char *part1 = "0\r\n\r\n";

	// Send HTTP request
	send(clientSocket, httpRequest, 27 + 17 + 28 + 2 + 3 + 7 + 3 + 6, 0);
	sleep(1);
	send(clientSocket, part1, 5, 0);

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

	std::cout << buffer << std::endl;

	// Close socket
	close(clientSocket);

	return 0;
}
