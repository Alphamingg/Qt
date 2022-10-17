#!/bin/bash


# ./setCPUMaxHZ.sh 1.6G
# ./setCPUMaxHZ.sh 2.0G
# ./setCPUMaxHZ.sh 3.6G

cpupower frequency-set -u $1

#cpupower frequency-info

