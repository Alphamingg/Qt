#!/bin/bash
if [ $# -eq 0 ];then
	echo "Usage: $0 <param>"
	echo "eg $0 43000 12000"
	exit 0
fi

#apt install stressapptest
#stressapptest -s 43000 -M 12000
#stressapptest -s 43000 -M 14000
#stressapptest -s 43000 -M 15000
#stressapptest -s 43000 -M 16000
#stressapptest -s 43000 -M 17000
#stressapptest -s 43000 -M 18000
#stressapptest -s 43000 -M 20000
#stressapptest -s 43000 -M 24000
stressapptest -s $1 -M $2


#下面的命令产生两个子进程，每个进程分配 300M 内存
#父进程处于睡眠状态，两个子进程负责资源消耗。
#Size="12000M"

#stress --vm  `nproc` --vm-bytes $Size --vm-keep

#stress --vm  `nproc` --vm-bytes $Size --vm-hang 5
#stress --vm  `nproc` --vm-bytes $Size --vm-stride 64
#stress --vm  `nproc` --vm-bytes $Size --vm-stride 1M
#--vm-keep
	#一直占用内存，区别于不断的释放和重新分配(默认是不断释放并重新分配内存)。
#--vm-hang N
	#指示每个消耗内存的进程在分配到内存后转入睡眠状态 N 秒，然后释放内存，一直重复执行这个过程。

#--vm-stride B
	#不断的给部分内存赋值，让 COW(Copy On Write)发生。
	#只要指定了内存相关的选项，这个操作就会执行，只是大小为默认的 4096。
	#赋值内存的比例由参数决定:	
		#for (i = 0; i < bytes; i += stride)
		#    ptr[i] = 'Z';           /* Ensure that COW happens.  */
	#该参数会影响 CPU 状态 us 和 sy：








