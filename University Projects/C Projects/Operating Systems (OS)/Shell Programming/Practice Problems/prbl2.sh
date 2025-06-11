#!/bin/bash

# Find recursively in a directory all ".c" files having more than 500 lines. Stop after finding 2 such files

OUT=0
for F in `find dir -name '*.c'`; do
	if [ `cat $F | wc -l` -ge 500 ]; then
		echo $F
		OUT=`expr $OUT + 1`
	fi
	if [ $OUT == 2 ]; then
		break
	fi
done
