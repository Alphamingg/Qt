#!/bin/bash

result=`mount |grep efi |grep nvme`

if [ ! -z "$result" ]
then 
	cat  /sys/block/nvme0n1/queue/scheduler
else
	cat  /sys/block/sda/queue/scheduler
fi

