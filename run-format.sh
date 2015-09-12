#!/usr/bin/env bash

for DIRECTORY in ./include ./test
do
    echo "Formatting code under $DIRECTORY/"
    find "$DIRECTORY" \( -name '*.h' -or -name '*.hh' -or -name '*.hpp' -or -name '*.c' -or -name '*.cc' -or -name '*.cpp' \) -print0 | xargs -0 "clang-format" -i
done
