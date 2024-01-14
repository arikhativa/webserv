#!/usr/bin/env python3

import sys
import os

file_path = 'res/nginx/html/cgi-bin/asd.mp4'

try:
    with open(file_path, 'rb') as file:
        content = file.read()
        sys.stdout.buffer.write(content)
except FileNotFoundError as e:
    print(f"The file was not found: {e}")
except PermissionError as e:
    print(f"You don't have permission to access this file: {e}")
except Exception as e:
    print(f"An unexpected error occurred: {e}")