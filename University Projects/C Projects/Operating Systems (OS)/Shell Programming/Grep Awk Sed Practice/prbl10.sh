#!/bin/bash

# Display all the distinct lines left in /etc/passwd after deleting all characters except "r"

cat passwd.fake | sed "s/[^r]//g" | sort | uniq
