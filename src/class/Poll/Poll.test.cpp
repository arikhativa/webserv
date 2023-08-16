
#include <Poll/Poll.hpp>
#include <gtest/gtest.h>

TEST(Poll, CreateDestroy)
{
	Poll *obj = new Poll();
	delete obj;
}

TEST(Poll, Canonical)
{
	Poll p;

	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8087);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
	{
		perror("bind");
		exit(1);
	}

	if (listen(serverSocket, 5) == -1)
	{
		perror("listen");
		exit(1);
	}

	int flags = fcntl(serverSocket, F_GETFL, 0);
	fcntl(serverSocket, F_SETFL, flags | O_NONBLOCK);

	p.addRead(serverSocket, Poll::newClient);
	p.loop();
}
