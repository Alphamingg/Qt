#!/bin/bash

if [ $# -eq 0 ];then
	echo "usage: $0 <pos>"
	echo "eg: $0 x y"
	echo "<pos> is the position of mouse"
	exit 0
fi

x=$1
y=$2
xdotool mousemove $x $y
