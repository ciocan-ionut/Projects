#!/bin/bash

# Display all the distinct lines left in /etc/passwd after deleting all letter and digits and spaces

cat passwd.fake | sed "s/[a-z]//g; s/[A-Z]//g; s/[0-9]//g; s/ //g" | sort | uniq
