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
	std::string identificador = body.substr(0, body.find("\r\n"));
	std::string content = body.substr(body.find(identificador) + identificador.length() + 2);
	content = content.substr(0, content.find(identificador) - 2);
	content = content.substr(content.find("\r\n\r\n") + 4);
	return (content);
}

bool	httprequesthandlerPOST::exists_file(const std::string& path)
{
	struct stat statbuf;
	return (stat(path.c_str(), &statbuf) == 0);
}

bool	httprequesthandlerPOST::is_directory(const std::string& path)
{
	struct stat statbuf;
	stat(path.c_str(), &statbuf);
	return (S_ISDIR(statbuf.st_mode));
}

bool	httprequesthandlerPOST::is_directory_writable(const std::string& path)
{
	return (exists_file(path) && is_directory(path) && access(path.c_str(), W_OK) == 0);
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
		return (query.substr(0, query.find("?")));
	return (query);
}

std::string httprequesthandlerPOST::getQueryCGIArgs(std::string request)
{
	std::string query = "";
	std::size_t pos = request.find("?");
	if (pos != std::string::npos)
	{
		std::size_t pos2 = request.find(" ", pos);
		if (pos2 != std::string::npos)
			query = request.substr(pos + 1, pos2 - pos - 1);
	}
	return (query);
}

bool	httprequesthandlerPOST::isChunked(std::string request)
{
	std::size_t pos = request.find("Transfer-Encoding: chunked");
	if (pos != std::string::npos)
		return (true);
	return (false);
}

std::string	httprequesthandlerPOST::getUnchunkedBody(std::string bodyRequest)
{
	std::string body;
	std::size_t pos = 0;
	while ((pos = bodyRequest.find("\r\n")) != std::string::npos)
	{
		std::string size = bodyRequest.substr(0, pos);
		std::stringstream ss;
		ss << std::hex << size;
		size_t size_int;
		ss >> size_int;
		if (size_int == 0)
			break;
		bodyRequest = bodyRequest.substr(size_int + 2);
		if (bodyRequest.length() < size_int + 2)
			throw HTTPRequestHandler::SizeError();
		body += bodyRequest.substr(0, size_int);
		if (bodyRequest.substr(size_int, 2) != "\r\n")
			throw HTTPRequestHandler::SizeError();
		bodyRequest = bodyRequest.substr(size_int + 2);
	}
	return (body);
}

char 	**httprequesthandlerPOST::setEnv(std::string bodyRequest, const std::string& path, std::string request, Server server)
{
	std::map<std::string, std::string>	env;
	(void)server;
	env["CONTENT_LENGTH"] = bodyRequest.length();
	std::size_t pos = request.find("Content-Type: ");
	if (pos != std::string::npos)
	{
		std::string content_type = request.substr(pos + 14);
		pos = content_type.find("\r\n");
		if (pos != std::string::npos)
			content_type = content_type.substr(0, pos);
		env["CONTENT_TYPE"] = content_type;
	}
	env["REQUEST_METHOD"] = request.substr(0, request.find(" "));
	env["SCRIPT_FILENAME"] = path;
	env["QUERY_STRING"] =  getQueryCGIArgs(request);
	env["SERVER_PROTOCOL"] = request.substr(request.find(" ") + 1, request.find("\r\n") - request.find(" ") - 1);
	env["SERVER_PORT"] = "1234" ;//std::to_string(server.getPort());
	env["SERVER_NAME"] = "localhost";//server.getServerName();
	//upload_dir
	env["UPLOAD_DIR"] = "/home/rufo/Desktop/42/"; //server.getUploadDir();

	char **ch_env = (char **)calloc(sizeof(char *), env.size() + 1);
	std::map<std::string, std::string>::const_iterator it = env.begin();
	for (int i = 0; it != env.end(); it++, i++)
	{
		std::string tmp = it->first + "=" + it->second;
		ch_env[i] = strdup(tmp.c_str());
	}
	ch_env[env.size()] = NULL;
	return (ch_env);
}

std::string httprequesthandlerPOST::createpipe(char **ch_env, char **argv, std::string bodyRequest)
{
	int pipe_in[2];
	int pipe_out[2];
	if (pipe(pipe_in) < 0 || pipe(pipe_out) < 0)
		return ("");
	int _exit_status;
	int pid = fork();
	if (pid < 0)
		return ("");
	if (pid == 0)
	{
		dup2(pipe_in[0], STDIN_FILENO);
		dup2(pipe_out[1], STDOUT_FILENO);
		close(pipe_in[0]);
		close(pipe_in[1]);
		close(pipe_out[0]);
		close(pipe_out[1]);
		_exit_status = execve(argv[0], argv, ch_env);
		exit(_exit_status);
	}
	else if (pid > 0)
	{
		close(pipe_in[0]);
		close(pipe_out[1]);
		write(pipe_in[1], bodyRequest.c_str(), bodyRequest.size());
		close(pipe_in[1]); 
		
		char    buffer[40000  * 2];
		size_t bytes_read = 0;
		std::string output;

		waitpid(pid, &_exit_status, 0);
		while ((bytes_read = read(pipe_out[0], buffer, sizeof(buffer))) > 0)
		{
			output.append(buffer, bytes_read);
			if (output.find("Content-Length: ") != std::string::npos)
			{
				std::size_t pos = output.find("Content-Length: ");
				std::string content_length = output.substr(pos + 16);
				pos = content_length.find("\r\n");
				if (pos != std::string::npos)
					content_length = content_length.substr(0, pos);
				std::stringstream ss;
				ss << content_length;
				size_t size_int;
				ss >> size_int;
				if (size_int == output.length() - pos - 2)
					break;
			}
		}
		for (int i = 0; argv[i] != NULL; i++)
			free(argv[i]);			
		free(argv);
		for (int i = 0; ch_env[i] != NULL; i++)
			free(ch_env[i]);
		free(ch_env);
		return (output);
	}
	return ("");
}

std::string httprequesthandlerPOST::getCGI(const std::string& path, Server server, std::string request, ResponseHeader &response)
{
	//!temporal
	std::map<std::string, std::string> cgi;//=server.get....();
	cgi[".py"] = "/usr/bin/python3";
	cgi[".php"] = "/usr/bin/php-cgi";
	cgi[".sh"] = "/usr/bin/sh";

	(void)server;
	std::string bodyRequest;
	if (request.find("\r\n\r\n") != std::string::npos)
		bodyRequest = request.substr(request.find("\r\n\r\n") + 4);
	else
		bodyRequest = "";
	if (isChunked(request))
		bodyRequest = getUnchunkedBody(bodyRequest);

	char **ch_env;
	ch_env = setEnv(bodyRequest, path,  request, server);
	std::string ext_path;
	ext_path = cgi[path.substr(path.find_last_of("."))];
	std::string cgi_path = path; 
	char **argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = strdup(ext_path.c_str());
	argv[1] = strdup(cgi_path.c_str());
	argv[2] = NULL;
	std::string content = createpipe(ch_env, argv, bodyRequest);
	std::size_t pos = content.find("Content-Type: ");
	std::string content_type = "";
	if (pos != std::string::npos)
	{
		content_type = content.substr(pos);
		std::size_t pos2 = content_type.find("\n");
		if (pos2 != std::string::npos)
		{
			
			content_type = content.substr(pos , pos2);
			pos  = content_type.find(":");
			content_type = content_type.substr(pos + 2);
			response.setContentType(content_type);
		}
	}

	pos = content.find("\r\n\r\n");
	if (pos != std::string::npos)
		content = content.substr(pos + 4);
	//si contiene content-type lo quito
	if (content_type != "")
	{
		pos = content.find(content_type);
		if (pos != std::string::npos)
			content = content.substr(pos + content_type.size() + 2);
	}
	return (content);
}

std::string httprequesthandlerPOST::getFileContent(const std::string& path, Server server, std::string request, ResponseHeader &response)
{
	//!temporal
	std::map<std::string, std::string> cgi;//=server.get....();
	cgi[".py"] = "/usr/bin/python3";
	cgi[".php"] = "/usr/bin/php-cgi";
	cgi[".sh"] = "/usr/bin/sh";

	if (path.find(".") != std::string::npos)
	{
		std::string ext = path.substr(path.find_last_of("."));
		if (cgi.find(ext) != cgi.end())
			return (getCGI(path, server, request, response));
	}
	std::ifstream file(path.c_str());
	if (!file)
		return std::string();
	std::stringstream contentStream;
	contentStream << file.rdbuf();
	file.close();
	std::string content = contentStream.str();
	if (path.find(".") != std::string::npos)
		response.setContentType(path.substr(path.find_last_of(".")));
	return (content);
}
