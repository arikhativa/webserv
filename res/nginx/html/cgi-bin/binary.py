#!/usr/bin/env python3

import sys
import os

print("Content-type: application/octet-stream\r")
print("\r")

request_body = sys.stdin.buffer.read()

sys.stdout.buffer.write(request_body)
