#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
	// Create a socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		perror("socket");
		return 1;
	}

	// Set up the server address structure
	sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(80);
	if (inet_pton(AF_INET, "0.0.0.0", &server_addr.sin_addr) <= 0)
	{
		perror("inet_pton");
		close(sockfd);
		return 1;
	}

	// Connect to the socket
	if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
	{
		perror("connect");
		close(sockfd);
		return 1;
	}

	// Data to send
	const char *data =
		// "POST /index.php HTTP/1.1\r\nHost: localhost:80\r\nTransfer-Encoding: chunked\r\n\r\n5\r\nhello\r\n";
		"POST /index.php HTTP/1.1\r\nHost: localhost:80\r\nTransfer-Encoding: chunked\r\n\r\n5\r\nhello\r\n0\r\n\r\n";
	size_t data_len = strlen(data);

	// Send data over the socket
	ssize_t bytes_sent = send(sockfd, data, data_len, 0);
	if (bytes_sent == -1)
	{
		perror("send");
		close(sockfd);
		return 1;
	}

	// Receive response from the socket
	char buffer[1024];
	ssize_t bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
	if (bytes_received == -1)
	{
		perror("recv");
		close(sockfd);
		return 1;
	}

	buffer[bytes_received] = '\0'; // Null-terminate the received data
	std::cout << buffer << std::endl;

	// Close the socket
	close(sockfd);

	return 0;
}
