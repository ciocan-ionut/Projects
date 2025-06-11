#!/bin/bash

# Display all the mounted file systems who are either smaller than than 1GB or have less than 20% free space.

cat df.fake | tail -n+2 | awk '{print $6,$2,$5}' | while read DIR SIZE USAGE; do
	if [ `echo "$SIZE" | sed 's/M//'` -lt 1000000 ]; then
		echo $DIR
		continue
	fi
	if [ `echo "$USAGE" | sed 's/%//'` -lt 20 ]; then
		echo $DIR
	fi
done
