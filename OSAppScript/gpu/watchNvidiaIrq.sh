#!/bin/bash

pid=`ps aux |grep irq |grep nvidia |awk '{ print $2}'`

if [ -z "$pid" ];then
	echo "No Nvidia"
else
	pidstat -ut 1 -p $pid
fi
