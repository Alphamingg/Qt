#!/bin/bash

power=$(nvidia-smi -q -d POWER | grep -F 'Min Power')
power="${power#*: }"
power="${power%.00 W}"

echo $power
