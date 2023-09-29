#!/usr/bin/env python3

import sys
import os

# Print necessary headers
print("Content-type: application/octet-stream\r")
print("\r")

# Read the request body and write it back
request_body = sys.stdin.buffer.read()
sys.stdout.buffer.write(request_body)
