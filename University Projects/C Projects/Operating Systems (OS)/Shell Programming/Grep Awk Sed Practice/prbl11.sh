#!/bin/bash

# Calculate the average of the PIDs of the processes currently running in the system

cat ps.fake | awk 'BEGIN {s=0; i=0} {s+=$2; i++} END {print s/i}'
