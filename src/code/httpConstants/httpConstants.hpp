
#ifndef HTTPCONSTANTS_HPP
#define HTTPCONSTANTS_HPP

#include <string>

namespace httpConstants
{
	static const std::string CARRIAGE_RETURN("\r");
	static const std::string NEW_LINE("\n");
	static const std::string FIELD_BREAK("\r\n");
	static const std::string HEADER_BREAK("\r\n\r\n");
	static const std::string HTML_SUFFIX(".html");
	static const std::string TXT_SUFFIX(".txt");
	static const std::string HTTP_VERSION("HTTP/1.1 ");
	static const std::string SERVER_FIELD_KEY("Server: ");
	static const std::string SERVER_FIELD_VALUE("webserv");
	static const std::string DATE_FIELD_KEY("Date: ");
	static const std::string CONTENT_TYPE_FIELD_KEY("Content-Type: ");
	static const std::string CONTENT_LENGHT_FIELD_KEY("Content-Length: ");
	static const std::string CONNECTION_FIELD_KEY("Connection: ");
	static const std::string ALLOW_HEADER("Allow: ");
	static const std::string CONNECTION_ALIVE("keep-alive");
	static const std::string CONNECTION_CLOSE("close");
	static const std::string SERVER_NAME("SERVER_NAME");
	static const std::string SERVER_PORT("SERVER_PORT");
	static const std::string SERVER_PROTOCOL("SERVER_PROTOCOL");
	static const std::string QUERY_STRING("QUERY_STRING");
	static const std::string SCRIPT_FILENAME("SCRIPT_FILENAME");
	static const std::string REQUEST_METHOD("REQUEST_METHOD");
	static const std::string CONTENT_TYPE("CONTENT_TYPE");
	static const std::string CONTENT_LENGTH("CONTENT_LENGTH");
	static const std::string UPLOAD_DIR("UPLOAD_DIR");
	static const std::string PREVIOUS_DIR("/..");
	static const std::string ACTUAL_DIR("/.");
	static const std::string SEPARATOR(":");
	static const std::string SPACE(" ");
} // namespace httpConstants

#endif
