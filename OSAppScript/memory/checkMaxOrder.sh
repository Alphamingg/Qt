#!/bin/bash

count=$(cat /proc/buddyinfo | awk 'NR==1{print NF}' )
#echo $count

if [ $count -eq 15 ];then
	echo "MAX_ORDER 11"
elif [ $count -eq 17 ];then
	echo "MAX_ORDER 13"
fi
