#!/bin/bash

if [ $# -eq 0 ];then
	echo "usage: $0 <param>"
	echo "<param> is the Processor ID of CPU"
	exit 0
fi

key="i915"

irqNum=`cat /proc/interrupts  |grep $key |awk '{print $1}' |sed 's/.$//'`
#当前绑定的CPU
#cat /proc/irq/$irqNum/smp_affinity_list

echo $1 > /proc/irq/$irqNum/smp_affinity_list
