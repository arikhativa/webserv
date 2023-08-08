#!/usr/bin/env python
import cgi
import sys
import os

# Get the form data from the request
form = cgi.FieldStorage()


env = os.environ["QUERY_STRING"]

pairs = env.split('&')

# Crear un diccionario para almacenar los pares clave-valor
result = {}
for pair in pairs:
    key, value = pair.split('=')
    result[key] = value

# Extract the form field values
name = result.get('name')
email = result.get('Email')
message = result.get('Message')

# Print out the form data
body = """
<html>
<body>
<h1>Form Data</h1>
<p>Name: %s</p>
<p>Email: %s</p>
<p>Message: %s</p>
</body>
</html>
""" % (name, email, message)

print ("Content-type: text/html\r")
print ("Content-Length: %d\r" % len(body))
print ("\r")
print(body)
