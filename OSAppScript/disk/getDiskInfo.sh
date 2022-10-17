#!/bin/bash
result=`mount |grep efi |grep nvme`
disk=""
if [ ! -z "$result" ]
then 
	#echo "[NVME]"
	disk="nvme0n1p1"
else
	disk="sda1"
fi

smartctl --all /dev/$disk
