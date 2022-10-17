#!/bin/bash

key="i915"

irqNum=`cat /proc/interrupts  |grep $key |awk '{print $1}' |sed 's/.$//'`
cat /proc/irq/$irqNum/smp_affinity_list
