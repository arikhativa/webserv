#!/usr/bin/env python3

import cgi
import sys
import os

# Get the request method and headers
method = os.environ.get("REQUEST_METHOD", "GET")
headers = {}

for key, value in os.environ.items():
    if key.startswith("HTTP_"):
        headers[key[5:].replace("_", "-").title()] = value

# Get the request body for POST requests
if method == "POST":
    content_length = int(os.environ.get("CONTENT_LENGTH", 0))
    request_body = sys.stdin.read(content_length)
else:
    request_body = ""

# Print the request method and headers
print(f"Request Method: {method}")
print("Headers:")
for key, value in headers.items():
    print(f"{key}: {value}")

# Print a blank line to separate headers from body
print()

# Print the request body
print("Request Body:")
print(request_body)
