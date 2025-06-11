#!/bin/bash

# Display the full names of the users having a username that starts with "m" and with a user ID divisible by 7

cat passwd.fake | awk -F: '$3%7==0 && $5~/^M/ {print $5}'
