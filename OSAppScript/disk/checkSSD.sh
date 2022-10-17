#!/bin/bash

export DISPLAY=:0.0
export PATH=$PATH:/usr/bin:/sbin

result=`mount |grep efi |grep nvme`

if [ ! -z "$result" ]
then 
	#echo "[NVME]"
	echo "SSD"
else
	#echo "[STAT]"
	isSSD=`cat /sys/block/sda/queue/rotational`

	if  [[ $isSSD = "0" ]];then
    	echo "SSD"
	else	
		echo "HDD"
	fi
fi

#isSSD=`cat /sys/block/sda/queue/rotational`
#
#if  [[ $isSSD = "0" ]];then
#    echo "SSD"
#else	
#	echo "HDD"
#fi
