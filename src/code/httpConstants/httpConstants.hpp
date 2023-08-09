
#ifndef HTTPCONSTANTS_HPP
#define HTTPCONSTANTS_HPP

#include <string>

namespace httpConstants
{
	const std::string CARRIAGE_RETURN("\r");
	const std::string NEW_LINE("\n");
	const std::string FIELD_BREAK("\r\n");
	const std::string HEADER_BREAK("\r\n\r\n");
	const std::string HTML_SUFFIX(".html");
	const std::string TXT_SUFFIX(".txt");
	const std::string HTTP_VERSION("HTTP/1.1 ");
	const std::string SERVER_FIELD_KEY("Server: ");
	const std::string SERVER_FIELD_VALUE("webserv");
	const std::string DATE_FIELD_KEY("Date: ");
	const std::string CONTENT_TYPE_FIELD_KEY("Content-Type: ");
	const std::string CONTENT_TYPE_FIELD("Content-Type");
	const std::string CONTENT_LENGHT_FIELD_KEY("Content-Length: ");
	const std::string CONNECTION_FIELD_KEY("Connection: ");
	const std::string ALLOW_HEADER("Allow: ");
	const std::string CONNECTION_ALIVE("keep-alive");
	const std::string CONNECTION_CLOSE("close");
	const std::string SERVER_NAME("SERVER_NAME");
	const std::string SERVER_PORT("SERVER_PORT");
	const std::string SERVER_PROTOCOL("SERVER_PROTOCOL");
	const std::string QUERY_STRING("QUERY_STRING");
	const std::string SCRIPT_FILENAME("SCRIPT_FILENAME");
	const std::string REQUEST_METHOD("REQUEST_METHOD");
	const std::string CONTENT_TYPE("CONTENT_TYPE");
	const std::string CONTENT_LENGTH("CONTENT_LENGTH");
	const std::string UPLOAD_DIR("UPLOAD_DIR");
	const std::string PATH_INFO("PATH_INFO");
	const std::string PREVIOUS_DIR("/..");
	const std::string ACTUAL_DIR("/.");
	const std::string SEPARATOR(":");
	const std::string SPACE(" ");
} // namespace httpConstants

#endif
