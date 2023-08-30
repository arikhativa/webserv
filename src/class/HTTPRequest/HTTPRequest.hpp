
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

class HTTPRequest
{
  public:
	static const int MAX_CHUNK_ATTEMPTS;
	explicit HTTPRequest();
	explicit HTTPRequest(Server *virtualServer, int client_fd);
	~HTTPRequest();

	BasicHTTPRequest getBasicRequest(void) const;
	std::string getResponse(void) const;
	int getClientFd(void) const;
	int getRequestAttempts(void) const;
	int getResponseAttempts(void) const;
	long unsigned int getBytesSent(void) const;
	Server *getVirtualServer(void) const;
	Socket *getSocket(void) const;

	void setBasicRequest(BasicHTTPRequest request);
	void setResponse(std::string response);
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
	Server *_virtualServer;
	Socket *_socket;
	int _clientFd;

	int _requestAttempts;
	int _responseAttempts;
	long unsigned int _bytesSent;
	std::string _rawRequest;
	std::string _response;
	BasicHTTPRequest _basicRequest;
};

std::ostream &operator<<(std::ostream &o, HTTPRequest const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* H_T_T_P_REQUEST_HPP */
