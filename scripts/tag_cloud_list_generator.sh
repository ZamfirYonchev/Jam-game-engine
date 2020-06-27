#!/bin/bash
find | grep "\.cpp$" | xargs cat | grep -v "^[[:space:]]*#" | grep -v "^[[:space:]]*/\*" | grep -v "^[[:space:]]*//" | grep -v "\*/[[:space:]]*$" | grep -v "Created on" | grep -v "Author" | grep -v "cpp" > contents
find | grep "\.h$" | xargs cat | grep -v "^[[:space:]]*#" | grep -v "^[[:space:]]*/\*" | grep -v "^[[:space:]]*//" | grep -v "\*/[[:space:]]*$" | grep -v "Created on" | grep -v "Author" | grep -v "cpp" >> contents
sed -i "s/[{};()\+\/\=\!\%\|\^\.\,\?]/ /g" contents
sed -i "s/->/ /g" contents
