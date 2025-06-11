#!/bin/bash

while true; do
	read lit
	if [ "$lit" == "$" ]; then
		break
	fi
	for F in $@; do
		if file "$F" | grep -q "text"; then
			echo "$F e un fisier text!"
			linii=`cat $F | wc -l`
			echo "$F are $linii linii"
			if [ `expr $linii % 2` -eq 1 ]; then
				echo "$lit" >> "$F"
			fi
			cat $F | while read l; do
				chr=`echo $l | wc -m`
				echo "$chr"
			done
		fi
	done
done
