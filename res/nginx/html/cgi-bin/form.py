#!/usr/bin/env python3

import cgi

# Print necessary headers
print("Content-type: text/html\r")
print("\r")
print("\r")

# Get form data
form = cgi.FieldStorage()

# Generate HTML response
print("<html><body>")
print("<h1>Form Data</h1>")
print("<ul>")

for field in form.keys():
    value = form.getvalue(field)
    print(f"<li>{field}: {value}</li>")

print("</ul>")
print("</body></html>")