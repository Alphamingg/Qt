#!/bin/bash

if [ $# -eq 0 ];then
	echo "usage: $0 <Gorvorner>"
	echo "<Gorvorner> is one of the available governors"
	exit 0
fi

Gorvorner=$1;
for i in $(ls /sys/devices/system/cpu/*/cpufreq/scaling_governor);
do 
#	cat $i
	echo $1 > $i;
done
