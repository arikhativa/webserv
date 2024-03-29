
#ifndef H_T_T_P_REQUEST_HPP
#define H_T_T_P_REQUEST_HPP

#include <BasicHTTPRequest/BasicHTTPRequest.hpp>
#include <HTTPRequestHandler/HTTPRequestHandler.hpp>
#include <Socket/Socket.hpp>
#include <header/header.hpp>
#include <matcher/matcher.hpp>
#include <vectorUtils/vectorUtils.hpp>

#include <iostream>
#include <map>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class HTTPCall
{
  public:
	static const int MAX_CHUNK_ATTEMPTS;
	static const int RECV_BUFFER_SIZE;
	HTTPCall();
	HTTPCall(const HTTPCall &src);
	explicit HTTPCall(const Socket *socket, int client_fd);
	~HTTPCall();

	HTTPCall operator=(const HTTPCall &rhs);

	BasicHTTPRequest &getBasicRequest(void);
	const BasicHTTPRequest &getBasicRequest(void) const;

	CgiManager *getCgi(void) const;
	const std::vector< char > &getResponse(void) const;
	std::string getResponseAsString(void) const;
	std::string getClientHostHeader(void) const;
	int getClientFd(void) const;
	long unsigned int getBytesSent(void) const;
	const Socket *getSocket(void) const;
	std::list< const IErrorPage * > getErrorPages(void) const;
	void parseRawRequest(void);
	bool isCGI(void) const;
	const IServerConf *getServerConf(void) const;
	const ILocation *getLocation(void) const;
	const Path &getLocalPath(void) const;
	std::string getExtension(void) const;

	void setBasicRequest(const BasicHTTPRequest &request);
	void setResponse(const std::vector< char > &response);
	void setClientFd(int fd);
	void setServerConf(const IServerConf *server_conf);
	void setLocation(const ILocation *location);
	void setCgi(CgiManager *cgi);

	bool isRedirect(void);
	bool isRequestAllowed(void);
	bool isCGIValid(void);
	bool isCGIPostExtValid(void);
	void setInvalidResponse(void);
	void setInternalServerResponse(void);
	void finalizeRequest(void);
	void recvRequest(void);
	void sendResponse(void);
	void handleRequest(void);

	void cgiToResponse(void);

	class SendingResponseError : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

	class SendingResponseEmpty : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

	class ReceivingRequestError : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

	class ReceivingRequestEmpty : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

  private:
	const Socket *_socket;
	int _client_fd;
	CgiManager *_cgi;

	long unsigned int _bytes_sent;
	std::vector< char > _response;
	BasicHTTPRequest _basic_request;
	const IServerConf *_server_conf;
	const ILocation *_location;
	Path _local_path;

	void _setLocalPath(void);
	bool _isMethodAllowed(void);
	bool _isBodySizeAllowed(void);
	bool _isCGIFileExist(void);
	bool _isCGIExecExist(void);
};

std::ostream &operator<<(std::ostream &o, HTTPCall const &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* H_T_T_P_REQUEST_HPP */
