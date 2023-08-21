body = "this is a test for the content_length"
trash = "this is a trash for the content_length"

print("Content-type: text/plain\r")
print("Content-Length: %d\r\n\r"% len(body))
print(body)
print(trash)