#!/usr/bin/python3
import cgi
import sys
import os
import time

form = cgi.FieldStorage()

print(os.environ["QUERY_STRING"])