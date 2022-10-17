#!/bin/bash

#./setCPUMinHZ.sh 0.8G
#./setCPUMinHZ.sh 1.2G

cpupower frequency-set -d $1

#cpupower frequency-info

