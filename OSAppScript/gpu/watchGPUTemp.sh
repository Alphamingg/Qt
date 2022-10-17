#!/bin/bash
isNvidia=`nvidia-smi -q | grep "failed"`
if [ -z "$isNvidia" ];then
	
	nvidia-smi --query-gpu=temperature.gpu --format=csv,noheader,nounits

	echo
	echo

	watch -n 1 -d "nvidia-smi  -q |grep Temp"
else
	echo "No Nvidia"
fi


