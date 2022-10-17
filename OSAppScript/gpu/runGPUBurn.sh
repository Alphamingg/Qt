#!/bin/bash

run()
{
	cd /home/devel/script/GPUInfo/gpu-burn/
	./gpu_burn 60
}

#basic stability: 30M
testBasic()
{

isNvidia=`nvidia-smi -q | grep "failed"`
if [ -z "$isNvidia" ];then

	for i in {1..30}:
	do
		run
	done
else
	echo "No Nvidia"
fi

}

#great stability: 1H
testGreat()
{
	for i in {1..60}:
	do
		run
	done
}

#guaranteed stability: 8H
testGuaranteed()
{
	for i in {1..8}:
	do
		testGreat
	done
}

#run
testBasic
#testGreat
#testGuaranteed
