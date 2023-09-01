
#ifndef H_T_T_P_REQUEST_HPP
#define H_T_T_P_REQUEST_HPP

#include <BasicHTTPRequest/BasicHTTPRequest.hpp>
#include <HTTPRequestHandler/HTTPRequestHandler.hpp>
#include <Server/Server.hpp>
#include <iostream>
#include <map>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class HTTPCall
{
  public:
	static const int MAX_CHUNK_ATTEMPTS;
	static const int RECV_BUFFER_SIZE;
	explicit HTTPCall(const Server *virtualServer, int client_fd);
	~HTTPCall();

	BasicHTTPRequest getBasicRequest(void) const;
	std::string getResponse(void) const;
	int getClientFd(void) const;
	int getRequestAttempts(void) const;
	int getResponseAttempts(void) const;
	long unsigned int getBytesSent(void) const;
	const Server *getVirtualServer(void) const;
	Socket *getSocket(void) const;

	void setBasicRequest(const BasicHTTPRequest &request);
	void setResponse(const std::string &response);
	void setClientFd(int fd);

	BasicHTTPRequest::Type getRequestType(void);
	void recvRequest(void);
	void sendResponse(void);
	void handleRequest(void);
	void terminate(void);

	class SendingResponseError : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

	class RecievingRequestError : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

  private:
	const Server *_virtual_server;
	Socket *_socket;
	int _client_fd;

	int _request_attempts;
	int _response_attempts;
	long unsigned int _bytes_sent;
	std::string _response;
	BasicHTTPRequest _basic_request;
};

std::ostream &operator<<(std::ostream &o, HTTPCall const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* H_T_T_P_REQUEST_HPP */
