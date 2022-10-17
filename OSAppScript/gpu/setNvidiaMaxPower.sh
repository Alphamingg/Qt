#!/bin/bash

power=$(nvidia-smi -q -d POWER | grep -F 'Max Power')
power="${power#*: }"
power="${power%.00 W}"

logger "	setNvidiaMaxPower[$power] "

nvidia-smi  -pm 1
nvidia-smi  -pl "$power"


