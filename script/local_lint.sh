#!/bin/bash

sed -i '10s/^/alias clang-format="clang-format -style=file:/tmp/.clang-format\n" /' /action/lib/linter.sh

/action/lib/linter.sh