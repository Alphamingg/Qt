#!/bin/bash

power=$(nvidia-smi -q -d POWER | grep -F 'Max Power')
power="${power#*: }"
power="${power%.00 W}"

echo $power
