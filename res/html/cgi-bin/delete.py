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
if method == "DELETE":
    request_body = "this is a delete request"
else:
    request_body = "empty req"

# Print the request body within a <p> element
print(f"{request_body}")