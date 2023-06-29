# Webserv


# Not Ready Yet :)

Webserv is a project developed as part of the curriculum at 42 School. It is a basic HTTP server implementation that supports static and dynamic content, and handles GET and POST requests.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Configuration](#configuration)
- [Contributing](#contributing)
- [License](#license)

## Features

- HTTP/1.1 protocol implementation
- Support for GET and POST requests
- Configurable server behavior through a configuration file
- Support for serving static files
- Dynamic content generation with CGI scripts
- Response codes and headers handling
- Logging of server activity
- Multi-threaded architecture for handling concurrent connections

## Installation

1. Clone the repository:

git clone https://github.com/your-username/webserv.git


2. Change into the project directory:
```
cd webserv
```

3. Compile the project:
```
make
```

## Usage

To start the server, run the following command:
```
./webserv <config-file>
```

Replace `<config-file>` with the path to your configuration file.

## Configuration

The server behavior can be configured using a configuration file in the following format:
```
[server]
port = <port-number>
host = <host-name>

[location]
route = <route>
root = <root-path>
cgi = <cgi-path>
```

- `port`: The port number on which the server will listen for incoming connections.
- `host`: The host name or IP address to bind the server to.
- `route`: The URL route for which the configuration applies.
- `root`: The path to the directory containing the static files to serve.
- `cgi`: The path to the directory containing the CGI scripts.

You can define multiple `[location]` sections in the configuration file to handle different routes.

## Contributing

Contributions are welcome! If you would like to contribute to this project, please follow these steps:

1. Fork the repository.
2. Create a new branch.
3. Make your changes and commit them.
4. Push your changes to your forked repository.
5. Submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).

