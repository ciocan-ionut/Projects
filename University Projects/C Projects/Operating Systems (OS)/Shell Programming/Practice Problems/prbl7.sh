#!/bin/bash

# Consider a file containing a username on each line.
# Generate a comma-separated string with email addresses of the users that exist.
# The email address will be obtained by appending "@scs.ubbcluj.ro" at the end of each username.
# Make sure the generated string does NOT end in a comma.

N=`cat usernames.txt | wc -l`
N=`expr $N - 1`
nr=0
MSG=""
cat usernames.txt | sed -E "s/$/@scs.ubbcluj.ro/g" | while read USER; do
	MSG="$MSG$USER"
	if [ $nr -lt $N ]; then
		MSG="$MSG,"
	fi
	nr=`expr $nr + 1`
	if [ $nr -gt $N ]; then
		echo $MSG
	fi
done
