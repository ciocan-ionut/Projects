#!/bin/bash

# Display a report showing the full name of all the users currently connected,
# and the number of processes belonging to each of them

awk '{print $1}' who.fake | while read NAME; do
	echo $NAME `grep -E "^$NAME" ps.fake | wc -l`
done
