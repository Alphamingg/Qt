#!/bin/bash

if [ $# -eq 0 ];then
	echo "usage: $0 <param>"
	echo "<param> is the CPUId and PID, eg: $0 0 14223"
	exit 0
fi

cpuId=$1
pid=$2
taskset -cp $cpuId $pid
