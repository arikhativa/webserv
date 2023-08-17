
#include <pollHandler/pollHandler.hpp>

Poll::ret_stt pollHandler::writeClient(Poll &p, int fd, int revents, void *call)
{
	if (revents == POLLOUT)
	{
		std::cout << "WriteClient => POLLOUT" << std::endl;
		std::string msg =
			"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Hello, World!</h1></body></html>\r\n";
		int bytesSent = send(fd, msg.c_str(), msg.length(), 0);
		(void)bytesSent;

		return Poll::DONE;
	}
	return Poll::CONTINUE;
}

Poll::ret_stt pollHandler::readFile(Poll &p, int fd, int revents, void *call)
{
	if (revents != POLLIN)
		return Poll::CONTINUE;

	BasicHTTPRequest *req = reinterpret_cast<BasicHTTPRequest *>(call);

	if (!req)
	{
		std::cerr << "call is NULL" << std::endl;
		return Poll::ERROR;
	}
	p.addWrite(fd, writeClient, req);
}

Poll::ret_stt pollHandler::readClient(Poll &p, int fd, int revents, void *call)
{
	BasicHTTPRequest *req = reinterpret_cast<BasicHTTPRequest *>(call);
	if (!req)
	{
		std::cerr << "call is NULL" << std::endl;
		return Poll::ERROR;
	}

	if (revents == POLLIN)
	{
		std::cout << "ReadClient => POLLIN" << std::endl;

		char buffer[1000];

		int bytesReceived = recv(fd, buffer, sizeof(buffer), 0);

		if (bytesReceived > 0)
		{
			buffer[bytesReceived] = '\0';

			req->setRaw(buffer);
			req->parseRaw();

			p.addRead(fd, readFile, req);
			return Poll::DONE;
		}
		else if (bytesReceived == 0)
		{
			std::cout << "Connection closed by the client" << std::endl;
			return Poll::DONE;
		}
		else
		{
			perror("recv");
		}
	}
	return Poll::CONTINUE;
}

Poll::ret_stt pollHandler::newClient(Poll &p, int fd, int revents, void *call)
{
	(void)call;
	if (revents == POLLIN)
	{
		std::cout << "newClient => POLLIN" << std::endl;
		int clientSocket = accept(fd, NULL, NULL);
		if (clientSocket > 0)
		{
			int flags = fcntl(clientSocket, F_GETFL, 0);
			fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK);

			p.addRead(clientSocket, readClient);
			return Poll::CONTINUE;
		}
	}
	return Poll::ERROR;
}
