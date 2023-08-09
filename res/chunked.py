#!/usr/bin/env python
import sys
import os

def read_chunk():
    chunk_size_line = sys.stdin.readline().strip()
    if not chunk_size_line:
        return None
    chunk_size = int(chunk_size_line, 16)
    if chunk_size == 0:
        return None
    return sys.stdin.read(chunk_size)

def main():
    print("Content-Type: text/plain")
    print("Transfer-Encoding: chunked")
    print()

    while True:
        chunk = read_chunk()
        if chunk is None:
            break

        os.system("sleep 15")
        print(hex(len(chunk))[2:])
        print(chunk)
        # wait 4 seconds
        sys.stdout.flush()

if __name__ == "__main__":
    main()
