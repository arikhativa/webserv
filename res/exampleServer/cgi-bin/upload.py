#!/usr/bin/env python3
import os
import sys

script_dir = os.path.dirname(os.path.abspath(__file__))
upload_dir = os.path.join(script_dir, '..', 'uploads')

data = sys.stdin.read()

header_separator = '\r\n\r\n'
separator_pos = data.find(header_separator)

headers = data[:separator_pos]
content = data[separator_pos + len(header_separator):]

file_start = content.find('\r\n\r\n') + 4
file_content = content[file_start:]

file_name = headers.splitlines()[1].split(';')[2].split('=')[1].strip('"')
file_path = os.path.join(upload_dir, file_name)

with open(file_path, 'wb') as f:
    f.write(file_content.encode())

print("Content-type: text/html\n")
print("<html>")
print("<body>")
print("<h2>File uploaded and saved successfully.</h2>")
print("</body>")
print("</html>")
