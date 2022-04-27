#!/bin/bash

name="$1" && gcc -x c -std=c17 -o $name ./$name.c && echo "Compiled successfuly" && ./$name

exit $?
