
#ifndef H_T_T_P_REQUEST_HPP
#define H_T_T_P_REQUEST_HPP

#include <iostream>
#include <string>
#include <sys/socket.h>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class HTTPRequest
{
  public:
	explicit HTTPRequest(int client_fd);
	HTTPRequest(HTTPRequest const &src);
	~HTTPRequest();

	HTTPRequest &operator=(HTTPRequest const &rhs);

	std::string getRawRequest(void) const;
	std::string getResponse(void) const;
	int getClientFd(void) const;

	void recvRequest(void);
	void sendResponse(void);
	void handleRequest(void);

  private:
	int _clientFd;
	std::string _rawRequest;
	/* TODO: how do we send files? */
	std::string _response;
};

std::ostream &operator<<(std::ostream &o, HTTPRequest const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* H_T_T_P_REQUEST_HPP */
