#include <IStatusCodes/IStatusCodes.hpp>

std::map<int, std::string> IStatusCodes::create_map()
{
	std::map<int, std::string> ret;
	// Informational 1xx
		ret[100] = "Continue";
		ret[101] = "Switching Protocols";

		// Successful 2xx
		ret[200] = "OK";
		ret[201] = "Created";
		ret[202] = "Accepted";
		ret[203] = "Non-Authoritative Information";
		ret[204] = "No Content";
		ret[205] = "Reset Content";
		ret[206] = "Partial Content";

		// Redirection 3xx
		ret[300] = "Multiple Choices";
		ret[301] = "Moved Permanently";
		ret[302] = "Found";
		ret[303] = "See Other";
		ret[304] = "Not Modified";
		ret[305] = "Use Proxy";
		ret[307] = "Temporary Redirect";

		// Client Error 4xx
		ret[400] = "Bad Request";
		ret[401] = "Unauthorized";
		ret[402] = "Payment Required";
		ret[403] = "Forbidden";
		ret[404] = "Not Found";
		ret[405] = "Method Not Allowed";
		ret[406] = "Not Acceptable";
		ret[407] = "Proxy Authentication Required";
		ret[408] = "Request Timeout";
		ret[409] = "Conflict";
		ret[410] = "Gone";
		ret[411] = "Length Required";
		ret[412] = "Precondition Failed";
		ret[413] = "Payload Too Large";
		ret[414] = "URI Too Long";
		ret[415] = "Unsupported Media Type";
		ret[416] = "Range Not Satisfiable";
		ret[417] = "Expectation Failed";
		ret[426] = "Upgrade Required";

		// Server Error 5xx
		ret[500] = "Internal Server Error";
		ret[501] = "Not Implemented";
		ret[502] = "Bad Gateway";
		ret[503] = "Service Unavailable";
		ret[504] = "Gateway Timeout";
		ret[505] = "HTTP Version Not Supported";
	return (ret);
}

std::map<int, std::string> IStatusCodes::_status_codes = create_map();