
#include <pollHandler/pollHandler.hpp>

Poll::ret_stt pollHandler::writeClient(Poll &p, int fd, int revents, Poll::Param param)
{
	(void)p;
	if (revents != POLLOUT)
		return Poll::CONTINUE;

	std::cout << "WriteClient => POLLOUT" << std::endl;

	std::ifstream file(param.req.getPath().c_str());
	if (!file.is_open())
	{
		std::cerr << "Error opening file." << std::endl;
		return Poll::ERROR;
	}

	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();

	HTTPResponse res("HTTP/1.1 200 OK\r\n");
	std::string tmp("Content-Length: ");

	tmp += converter::numToString<size_t>(content.length());
	tmp += "\r\n";

	res.extenedRaw(tmp);
	res.extenedRaw("Content-Type: text/html\r\n\r\n");
	res.extenedRaw(content);
	res.parseRaw();
	res.parseBody();

	std::cout << "Response: " << res << std::endl;

	int bytesSent = send(fd, res.toString().c_str(), res.toString().length(), 0);
	(void)bytesSent;

	return Poll::DONE;
}

Poll::ret_stt pollHandler::readClient(Poll &p, int fd, int revents, Poll::Param param)
{
	if (revents == POLLIN)
	{
		std::cout << "ReadClient => POLLIN" << std::endl;

		char buffer[1000];

		int bytesReceived = recv(fd, buffer, sizeof(buffer), 0);

		if (bytesReceived > 0)
		{
			buffer[bytesReceived] = '\0';

			param.req.setRaw(buffer);
			param.req.parseRaw();

			p.addWrite(fd, writeClient, param);
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

Poll::ret_stt pollHandler::newClient(Poll &p, int fd, int revents, Poll::Param param)
{
	if (revents == POLLIN)
	{
		std::cout << "newClient => POLLIN" << std::endl;
		int clientSocket = accept(fd, NULL, NULL);
		if (clientSocket > 0)
		{
			int flags = fcntl(clientSocket, F_GETFL, 0);
			fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK);

			param.src_socket = clientSocket;
			p.addRead(clientSocket, readClient, param);
			return Poll::CONTINUE;
		}
	}
	return Poll::ERROR;
}
