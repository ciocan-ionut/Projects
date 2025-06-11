#!/bin/bash -x

# Find recursively in a directory, all the files with the extension ".log"
# and sort their lines (replace the original file with the sorted content)

for F in `find dir -name "*.log"`; do
	cat $F | sort --output=$F
done
