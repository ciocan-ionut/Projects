#!/bin/bash

# Find all the distinct usernames starting with "r" that are currently running programs,
# and display them duplicating every vowel

cat ps.fake | awk '$1~/^r/ {print $1}' | sed -E "s/([aeiou])/\1\1/g" | sort | uniq
