#!/bin/bash

if [ $# -eq 0 ];then
	echo "usage: $0 <Energy>"
	echo "<Energy> is one of the available Energy"
	exit 0
fi

Energy=$1;
for i in $(ls /sys/devices/system/cpu/*/cpufreq/energy_performance_preference);
do 
#	cat $i
	echo $Energy > $i;
done
