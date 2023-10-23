# Webserv 🖥️

Webserv is a project developed as part of the curriculum at 42 School. It is a basic HTTP server implementation that supports static and dynamic content, and handles GET POST and DELETE requests.

## Table of Contents 📑

- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Configuration](#configuration)
- [Keywords](#keywords)
- [Authors](#authors)

## Requirements 📋

- HTTP/1.1 protocol implementation
- Support for GET POST and DELETE requests
- Configurable server behavior through a configuration file
- Support for serving static files
- Dynamic content generation with CGI scripts
- Response codes and headers handling

## Installation 🛠️

1. Clone the repository:

```
git clone https://github.com/your-username/webserv.git
```

2. Change into the project directory:
```
cd webserv
```

3. Compile the project:
```
make
```

## Usage 🔧

To start the server, run the following command:
```
./webserv <config-file>
```

Replace `<config-file>` with the path to your configuration file.

## Configuration 📁

The server behavior can be configured using a configuration file in a format based on nginx conf file.
<details>
  <summary> Basic Example</summary>

```
server {
	server_name pigafetta.com;
	listen 127.0.0.1:1234;

	root /var/www/html;

	location / {
		autoindex on;	
	}
}	

```
</details>
<details>
  <summary> Full Example</summary>

```
server {
	location /default {
	}
}

server {
	server_name antonio pigafetta;
	client_max_body_size 20;
	return 200 /200.html;
	root /asd;
	index 1.htm 2.htm 3.htm;
	listen 127.0.0.2:6660;

	location /DEL {
		allow_methods DELETE;
	}
}

server {
	server_name yoda.com;

	root /var/www/example.com;
	listen 1.1.2.2:89;
	listen 8.8.8.8:88;
	index 1.htm 2.htm 3.htm;
	error_page 404 /404.html;
	return 500 /500.html;
	client_max_body_size 100;


	location /loc1 {
		allow_methods POST;
		client_max_body_size 0;
		root /var/www/example1.com;
		index 1.htm 2.htm 3.htm;
		return 303 /303.html;
		autoindex on;
		cgi .py /usr/bin/python3;
	}

	location /loc2 {
		allow_methods GET POST;
		client_max_body_size 555;
		root /var/www/example2.com;
		index 1.htm 2.htm 3.htm;
		return 400 /400.html;
		autoindex off;
	}
	
}

```
</details>

### Keywords 🔑

- `server`: Configuration for a virtual server.
- `server_name`: The domain name or names associated with this particular server block, allowing it to respond to requests for those names.
- `root`: The absolute filesystem path to the directory that will be considered the root directory for serving files.
- `listen`: Defines the IP address and port number on which the server will listen for incoming connections.
- `index`: Specifies the default files to serve when a directory is requested.
- `error_page`: Specifies a file for which custom error pages should be displayed.
- `return`: Provides the ability to specify different HTTP response codes and associated content for specific paths.
- `client_max_body_size`: Sets the maximum allowed size for a client request body.
- `location`: Allows configuration based on the request path, enabling fine-grained control over how requests are handled.
- `allow_methods`: Specifies the HTTP methods allowed for a particular location.
- `autoindex`: Enables or disables directory listing if an index file is not found.
- `upload_store`: Defines the directory where uploaded files are stored.
- `cgi`: Defines the extension for gci file and the location of the cgi binary.

## Authors 👥

- [@arikhativa](https://github.com/arikhativa)
- [@llanahp](https://github.com/llanahp)
- [@dVaGaymer](https://github.com/dVaGaymer)
