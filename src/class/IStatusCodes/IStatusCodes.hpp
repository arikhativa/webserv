
#ifndef I_STATUS_CODES_HPP
#define I_STATUS_CODES_HPP

#include <list>
#include <string>
#include <iostream>
#include <map>


#ifdef TEST_ON
#define private public
#define protected public
#endif

class IStatusCodes
{
  protected:
	std::map<int, std::string> _status_codes;
  public:
	virtual ~IStatusCodes(){};
	IStatusCodes()
	{
		// Informational 1xx
		_status_codes[100] = "Continue";
		_status_codes[101] = "Switching Protocols";

		// Successful 2xx
		_status_codes[200] = "OK";
		_status_codes[201] = "Created";
		_status_codes[202] = "Accepted";
		_status_codes[203] = "Non-Authoritative Information";
		_status_codes[204] = "No Content";
		_status_codes[205] = "Reset Content";
		_status_codes[206] = "Partial Content";

		// Redirection 3xx
		_status_codes[300] = "Multiple Choices";
		_status_codes[301] = "Moved Permanently";
		_status_codes[302] = "Found";
		_status_codes[303] = "See Other";
		_status_codes[304] = "Not Modified";
		_status_codes[305] = "Use Proxy";
		_status_codes[307] = "Temporary Redirect";

		// Client Error 4xx
		_status_codes[400] = "Bad Request";
		_status_codes[401] = "Unauthorized";
		_status_codes[402] = "Payment Required";
		_status_codes[403] = "Forbidden";
		_status_codes[404] = "Not Found";
		_status_codes[405] = "Method Not Allowed";
		_status_codes[406] = "Not Acceptable";
		_status_codes[407] = "Proxy Authentication Required";
		_status_codes[408] = "Request Timeout";
		_status_codes[409] = "Conflict";
		_status_codes[410] = "Gone";
		_status_codes[411] = "Length Required";
		_status_codes[412] = "Precondition Failed";
		_status_codes[413] = "Payload Too Large";
		_status_codes[414] = "URI Too Long";
		_status_codes[415] = "Unsupported Media Type";
		_status_codes[416] = "Range Not Satisfiable";
		_status_codes[417] = "Expectation Failed";
		_status_codes[426] = "Upgrade Required";

		// Server Error 5xx
		_status_codes[500] = "Internal Server Error";
		_status_codes[501] = "Not Implemented";
		_status_codes[502] = "Bad Gateway";
		_status_codes[503] = "Service Unavailable";
		_status_codes[504] = "Gateway Timeout";
		_status_codes[505] = "HTTP Version Not Supported";
	};
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_STATUS_CODES_HPP */
