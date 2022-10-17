#!/bin/bash

if [ $# -eq 0 ];then
	echo "usage: $0 <param>"
	echo "<param> is the Priority value and PID. eg: $0 1 27123"
	exit 0
fi

pri=$1
pid=$2
chrt -p $pri $pid
