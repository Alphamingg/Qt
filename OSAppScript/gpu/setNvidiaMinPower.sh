#!/bin/bash

power=$(nvidia-smi -q -d POWER | grep -F 'Min Power')
power="${power#*: }"
power="${power%.00 W}"

logger "	setNvidiaMinPower[$power] "

nvidia-smi  -pm 1
nvidia-smi  -pl "$power"

