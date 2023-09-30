#!/usr/bin/env python3

import cgi
import sys
import os

# Print necessary headers
print("Content-type: text/html\r")
print("\r")
print("\r")

# Get the request method
method = os.environ.get("REQUEST_METHOD", "GET")

# Get the request body for POST requests
if method == "POST":
    content_length = int(os.environ.get("CONTENT_LENGTH", 0))
    request_body = sys.stdin.read(content_length)
else:
    request_body = ""

# Print the request body within a <p> element
print(f"{request_body}")