#!/usr/bin/env python3
import cgi
import cgitb
cgitb.enable()

# Print necessary headers
print("Content-type: application/octet-stream")
print()

# Get the uploaded file from the form data
form = cgi.FieldStorage()["userfile"]

# if "file" in form:
#     uploaded_file = form["file"]

#     # Set the response header to indicate the file name
#     # print(f"Content-Disposition: attachment; filename=\"{uploaded_file.filename}\"")

#     # Print a blank line to indicate the end of headers
#     # print()

#     # Write the file content to the response body
#     with open(uploaded_file.file.name, "rb") as file:
#         content = file.read()
        # print(content)

# else:
print("Status: 400 Bad Request")
print("\nContent-type: text/html")
print("\n")
print("<html><body>")
print("<h1>400 Bad Request</h1>")
print("<p>No file was uploaded.</p>")
print("</body></html>")