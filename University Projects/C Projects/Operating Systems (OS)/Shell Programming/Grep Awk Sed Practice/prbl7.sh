#!/bin/bash

# Find all usersnames starting with "t" that logged on "pts/9"

cat last.fake | awk '$1~/\<t/ && $2~/pts\/9/ {print $1}' | sort | uniq
