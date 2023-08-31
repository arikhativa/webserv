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

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

std::string generateChunkedBody(const std::string &filePath)
{
	std::ifstream inputFile(filePath, std::ios::binary);
	if (!inputFile)
	{
		std::cerr << "Failed to open file: " << filePath << std::endl;
		return "";
	}

	std::stringstream chunkedBody;
	char buffer[4096];
	while (!inputFile.eof())
	{
		inputFile.read(buffer, sizeof(buffer));
		std::streamsize bytesRead = inputFile.gcount();
		if (bytesRead > 0)
		{
			chunkedBody << std::hex << bytesRead << "\r\n";
			chunkedBody.write(buffer, bytesRead);
			chunkedBody << "\r\n";
		}
	}

	chunkedBody << "0\r\n\r\n"; // Final chunk

	return chunkedBody.str();
}

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
	std::string data("POST /index.php HTTP/1.1\r\nHost: localhost:80\r\nContent-Type: "
					 "multipart/form-data; charset=utf-8; boundary=1234\r\nTransfer-Encoding: chunked\r\n\r\n");

	data += generateChunkedBody("test.txt");

	size_t data_len = strlen(data.c_str());

	// Send data over the socket
	ssize_t bytes_sent = send(sockfd, data.c_str(), data_len, 0);
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
