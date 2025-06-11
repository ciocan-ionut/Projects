#!/bin/bash

# Find all the usernames that logged in from "economica" on a Sunday

cat last.fake | grep -E "economica" | grep -E "Sun" | awk '{print $1}' | sort | uniq
