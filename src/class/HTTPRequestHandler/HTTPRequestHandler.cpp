
#include <HTTPRequestHandler/HTTPRequestHandler.hpp>

IAllowedMethods::type HTTPRequestHandler::getRequestType(std::string request)
{
	if (!request.compare(0, AllowedMethods::GET.size(), AllowedMethods::GET))
		return (IAllowedMethods::GET);
	if (!request.compare(0, AllowedMethods::POST.size(), AllowedMethods::POST))
		return (IAllowedMethods::POST);
	if (!request.compare(0, AllowedMethods::DELETE.size(), AllowedMethods::DELETE))
		return (IAllowedMethods::DELETE);
	else
		throw AllowedMethods::InvalidMethodException();
}

std::string HTTPRequestHandler::GET(std::string request)
{
	return "You sent a GET request:\n---\n" + request + "---\n";
}

std::string HTTPRequestHandler::POST(std::string request)
{
	return "You sent a POST request:\n---\n" + request + "---\n";
}

std::string HTTPRequestHandler::DELETE(std::string request)
{
	return "You sent a DELETE request:\n---\n" + request + "---\n";
}

std::string HTTPRequestHandler::UNKNOWN(std::string request)
{
	return "You sent an UKNOWN request:\n---\n" + request + "---\n";
}