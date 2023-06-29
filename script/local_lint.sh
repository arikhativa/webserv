#!/bin/bash

# echo "alias clang-format="clang-format -style=file"" >> ~/.bashrc

sed -i '10s/^/alias clang-format="clang-format -style=file:/tmp/.clang-format\n" /' /action/lib/linter.sh

# cat /action/lib/linter.sh | grep clang-format

/action/lib/linter.sh