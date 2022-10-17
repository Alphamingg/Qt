#!/bin/bash

name="E5App"
#name="EUPSystemTool"
pid=`pidof $name`

#if [[ x$pid = x" " ]]
if [[ -z $pid ]]
then
	name="U2EApp"
	pid=`pidof $name`
fi

echo "$name PID: $pid"
echo "$name Info."
chrt -a -p $pid




