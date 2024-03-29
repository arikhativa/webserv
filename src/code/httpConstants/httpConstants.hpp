
#ifndef HTTPCONSTANTS_HPP
#define HTTPCONSTANTS_HPP

#include <string>

namespace httpConstants
{
	const std::string EMPTY_STRING("");
	const std::string CARRIAGE_RETURN("\r");
	const std::string NEW_LINE("\n");
	const std::string FIELD_BREAK("\r\n");
	const std::string HEADER_BREAK("\r\n\r\n");
	const std::string CHUNKED_END("0\r\n\r\n");
	const std::string HTML_SUFFIX(".html");
	const std::string TXT_SUFFIX(".txt");
	const std::string HTTP_VERSION("HTTP/1.1 ");
	const std::string HTTP_VERSION_PREFIX("HTTP/");
	const std::string SERVER_FIELD_KEY("Server: ");
	const std::string SERVER_FIELD_VALUE("webserv");
	const std::string DATE_FIELD_KEY("Date: ");
	const std::string CONTENT_TYPE_FIELD_KEY("Content-Type: ");
	const std::string HOST_HEADER("Host: ");
	const std::string CONTENT_TYPE_FIELD("Content-Type");
	const std::string CONTENT_LENGTH_FIELD_KEY("Content-Length: ");
	const std::string CONNECTION_FIELD_KEY("Connection: ");
	const std::string ALLOW_HEADER("Allow: ");
	const std::string CONNECTION_ALIVE("keep-alive");
	const std::string CONNECTION_CLOSE("close");
	const std::string CONTENT_TYPE("CONTENT_TYPE");
	const std::string UPLOAD_DIR("UPLOAD_DIR");
	const std::string PREVIOUS_DIR("/..");
	const std::string ACTUAL_DIR("/.");
	const std::string SEPARATOR(":");
	const std::string SPACE(" ");

	namespace cgi
	{
		const std::string SCRIPT_NAME("SCRIPT_NAME");
		const std::string SERVER_SOFTWARE("SERVER_SOFTWARE");
		const std::string PATH_INFO("PATH_INFO");
		const std::string CONTENT_LENGTH("CONTENT_LENGTH");
		const std::string CONTENT_TYPE("CONTENT_TYPE");
		const std::string REQUEST_METHOD("REQUEST_METHOD");
		const std::string QUERY_STRING("QUERY_STRING");
		const std::string SERVER_NAME("SERVER_NAME");
		const std::string SERVER_PORT("SERVER_PORT");
		const std::string SERVER_PROTOCOL("SERVER_PROTOCOL");
		const std::string SCRIPT_FILENAME("SCRIPT_FILENAME");
	} // namespace cgi

	namespace headers
	{
		const std::string JSON("application/json");
		const std::string DATE("Date");
		const std::string CONNECTION("Connection");
		const std::string CONTENT_LENGTH("Content-Length");
		const std::string CONTENT_TYPE("Content-Type");
		const std::string HOST("Host");
		const std::string TRANSFER_ENCODING("Transfer-Encoding");
		const std::string LOCATION("Location");
		const std::string CHUNKED("chunked");
		const std::string FROM_DATA("multipart/form-data");
	} // namespace headers
} // namespace httpConstants

#endif
