#!/usr/bin/env python3


print("Status: 403 Forbidden")
print("Content-Type: text/html")  # Set the content type to HTML
print()  # Print an empty line to signal the end of headers

# Generate the HTML content
print("<html>")
print("<head>")
print("<title>Simple CGI Script</title>")
print("</head>")
print("<body>")
print("<h1>Hello from CGI Script!</h1>")
print("<p>This is a simple CGI-generated HTML page.</p>")
print("</body>")
print("</html>")
