
#ifndef H_T_T_P_REQUEST_HPP
#define H_T_T_P_REQUEST_HPP

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
  private:
	enum type
	{
		GET,
		POST,
		DELETE,
		UNKNOWN
	};
	static const std::string GET_STRING;
	static const std::string POST_STRING;
	static const std::string DELETE_STRING;

  public:
	explicit HTTPRequest(const Server virtualServer, int client_fd);
	~HTTPRequest();

	std::string getRawRequest(void) const;
	std::string getResponse(void) const;
	int getClientFd(void) const;
	bool isCompleted(void) const;

	void setRawRequest(std::string request);
	void setResponse(std::string response);
	void setClientFd(int fd);

	type getRequestType(void);
	void recvRequest(void);
	void sendResponse(void);
	void handleRequest(void);

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
	bool _isCompleted;
	const Server _virtualServer;
	const int _clientFd;

	std::string _rawRequest;
	std::string _response;
};

std::ostream &operator<<(std::ostream &o, HTTPRequest const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* H_T_T_P_REQUEST_HPP */
