#!/bin/bash


isNvidia=`nvidia-smi -q | grep "failed"`
if [ -z "$isNvidia" ];then
	
	power=$(nvidia-smi -q -d POWER | grep -F 'Enforced Power Limit')
	power="${power#*: }"
	power="${power%.00 W}"

	echo $power
else
	echo "No Nvidia"
fi



