#!/bin/bash

# Find all users whose user ID has three digits and starts with 23

cat passwd.fake | awk -F: '$1~/023[0-9]/ {print $5}'
