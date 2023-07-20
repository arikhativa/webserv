#include <HTTPRequestHandler/httprequesthandlerGET.hpp>

bool	httprequesthandlerGET::exists_file(const std::string& path)
{
	struct stat statbuf;
	return (stat(path.c_str(), &statbuf) == 0);
}

bool	httprequesthandlerGET::is_directory(const std::string& path)
{
	struct stat statbuf;
	stat(path.c_str(), &statbuf);
	return (S_ISDIR(statbuf.st_mode));
}

std::string	httprequesthandlerGET::getFileContent(const std::string& path)
{
	std::ifstream file(path.c_str());
	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	return (content);
}

std::string httprequesthandlerGET::getFileDate(struct stat statbuf)
{
	char		buf[32];
	struct tm	*tm;

	tm = gmtime(&statbuf.st_mtime);
	int ret = strftime(buf, 32, "%d-%b-%Y %H:%M", tm);
	return (std::string(buf, ret));
}

std::map<std::string, std::string> httprequesthandlerGET::getParameters(std::string url)
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

std::string httprequesthandlerGET::getQuery(std::string request)
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

std::string httprequesthandlerGET::treat_url(std::string url)
{
	if (url.size() >= 3 && url.substr(url.length() - 3) == "/..")
	{
		size_t pos = url.find_last_of("/");
		if (pos != std::string::npos)
		{
			url = url.substr(0, pos);
			pos = url.find_last_of("/");
			if (pos != std::string::npos)
				url = url.substr(0, pos);
			else
				url = "/";
		}
	}
	if (url.size() >= 2 && url.substr(url.length() - 2) == "/.")
		url = url.substr(0, url.length() - 2);
	return (url);
}

std::string	httprequesthandlerGET::defineUrlDate(std::string path, std::string relative_path, struct dirent *ent, std::string date)
{
	std::ostringstream content;
	if (relative_path[0] != '/')
		relative_path = "/" + relative_path ;
	if (relative_path[relative_path.length() - 1] != '/')
		relative_path += "/";
	std::string url = treat_url(relative_path + ent->d_name);
	std::string name= std::string(ent->d_name);
	if (name.length() > 50)
		name = name.substr(0, 47) + "..>";
	int i = 0;
	if (is_directory(path) && url[url.length() - 1] != '/')
	{
		content << "<a href=\"" + url + "\">" + name + "/" + "</a>";
		i = -1;
	}
	else
		content << "<a href=\"" + url + "\">" + name+ "</a>";
	content << std::setw(68 + i - name.length()) << date;
	return (content.str());
}

std::string httprequesthandlerGET::getDirecoryContent(const std::string &path,  std::string &name)
{
	std::ostringstream content;
		content << "<!DOCTYPE html><html>\r\n<head><title>Index of " + name + "</title></head>\r\n";
		content << "<body>\r\n<h1>Index of " + name + "</h1><hr><pre>\n";
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir ((path + name).c_str())) != NULL)
	{
		while ((ent = readdir (dir)) != NULL)
		{
			struct stat statbuf;
			std::string path_aux(path + name + ent->d_name);
			stat(path_aux.c_str(), &statbuf);
			std::string date = getFileDate(statbuf);
			size_t size = statbuf.st_size;
			content << defineUrlDate(path_aux, name, ent, date);
			if (is_directory(path_aux))
				content << std::setw(20) << "-";
			else
				content << std::setw(20) << size;
			content << "<br>";
		}
		closedir (dir);
	}
	content << "</body>\n</html>";
	return (content.str());
}
