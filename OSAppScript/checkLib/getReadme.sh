#!/bin/bash

if [ $# -eq 0 ];then
	echo "usage:$0 <path>"
	echo "<path> is the path of Readme"
	exit
fi

path=$1
gedit $path
