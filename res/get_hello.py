#!/usr/bin/python3
import sys
import os

# Get data from fields
env = os.environ["QUERY_STRING"]


pairs = env.split('&')

# Crear un diccionario para almacenar los pares clave-valor
result = {}
for pair in pairs:
    key, value = pair.split('=')
    result[key] = value

# Extract the form field values
first_name = result.get('first_name')
last_name = result.get('last_name')

body = """
<html>
<body>
<h2>Hello, %s %s!</h2>
</body>
</html>
""" % (first_name, last_name)

print("Content-type: text/html\r")
print("Content-Length: %d\r" % len(body))
print ("\r")
print(body)