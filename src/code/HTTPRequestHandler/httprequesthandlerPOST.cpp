#include <HTTPRequestHandler/httprequesthandlerPOST.hpp>

std::string httprequesthandlerPOST::getBody(std::string request)
{
	std::string body = "";
	std::size_t pos = request.find("\r\n\r\n");
	if (pos != std::string::npos)
		body = request.substr(pos + 4);
	return (body);
}


std::string httprequesthandlerPOST::getNameFilePost(std::string body)
{
	std::string name = "";
	std::size_t pos = body.find("filename=\"");
	if (pos != std::string::npos)
	{
		std::size_t pos2 = body.find("\"", pos + 10);
		if (pos2 != std::string::npos)
			name = body.substr(pos + 10, pos2 - pos - 10);
	}
	return (name);
}

std::string httprequesthandlerPOST::getContentFilePost(std::string body)
{
	std::string content = "";
	std::size_t pos = body.find("\r\n\r\n");
	if (pos != std::string::npos)
		content = body.substr(pos + 4);
	return (content);
}


bool	httprequesthandlerPOST::exists_file(const std::string& path)
{
	struct stat statbuf;
	return (stat(path.c_str(), &statbuf) == 0);
}


std::map<std::string, std::string> httprequesthandlerPOST::getParameters(std::string url)
{
	std::string query = url.substr(url.find("?") + 1);
	std::map<std::string, std::string> map;
	std::string key;
	std::string value;
	std::size_t pos = 0;
	while ((pos = query.find("&")) != std::string::npos)
	{
		pos = query.find("&");
		key = query.substr(0, pos);
		value = "";
		std::size_t pos2 = key.find("=");
		if (pos2 != std::string::npos)
		{
			value = key.substr(pos2 + 1);
			key = key.substr(0, pos2);
		}
		map[key] = value;
		query = query.substr(pos + 1);
	}
	if (query != "")
	{
		key = query.substr(0, query.find("="));
		if (query.find("=") != std::string::npos)
			value = query.substr(query.find("=") + 1);
		else
			value = "";
		map[key] = value;
	}
	return (map);
}

std::string httprequesthandlerPOST::getQuery(std::string request)
{
	std::string query = "";
	std::size_t barra_pos = request.find("/");
	if (barra_pos != std::string::npos)
	{
		std::size_t espacio_pos = request.find(" ", barra_pos);
		if (espacio_pos != std::string::npos) 
			query = request.substr(barra_pos + 1, espacio_pos - barra_pos - 1);
	}
	std::size_t pos = 0;
	while ((pos = query.find("%20", pos)) != std::string::npos)
	{
		query.replace(pos, 3, " ");
		pos += 1;
	}
	if (query.find("?") != std::string::npos)
	{
		std::map<std::string, std::string> parameters = getParameters(query);
		//parameters will be used in the future for CGI
		return (query.substr(0, query.find("?")));
	}
	return (query);
}
