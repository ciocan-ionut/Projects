#!/bin/bash

# Find all the users that logged into the system after 11PM

cat last.fake | awk '$7 >= 23 {print $1}' | head -n -1| sort | uniq
