#!/bin/bash

if [ $# -eq 0 ];then
	echo "usage: $0 <folder>"
	echo "<folder> should be an absolute path"
	exit 0
fi

folder=${1%/}

function saveInfo(){

if [ ! -d $folder ];then
	#echo "`date` [INFO] $folder isn't a directory"
	exit 127
fi


find $folder -type f | grep "\.so$\|\.so\." | grep [0-9o]$ >> /tmp/allLibsTemp.txt

#去掉白名单的动态库
if [ -e ~/whiteList.conf ];then
	cat /tmp/allLibsTemp.txt | while read Line
	do
    	str="`cat ~/whiteList.conf | grep -w $Line`"
		if [ -z "$str" ];then
			echo $Line >> /tmp/allLibs.txt
		fi
	done
fi

cat /tmp/allLibs.txt | xargs -I{}  ldd {} | grep "not found" | awk '{print $1}' | sort | uniq >> /tmp/lddNotFound.txt

#更新数据库
#echo 'abc123' | sudo -S updatedb

echo "################################################################" >> /tmp/lddInfo.txt
date >> /tmp/lddInfo.txt

cat /tmp/lddNotFound.txt | while read Line
do

	str=`locate $Line`
	if [ -z "$str" ];then
		echo $Line >> /tmp/lddInfo.txt
	fi
done

#echo "$folder中所有系统缺失的动态库已存放/tmp/lddInfo.txt"
echo "################################################################" >> /tmp/lddInfo.txt
}



saveInfo
rm /tmp/lddNotFound.txt
rm /tmp/allLibs.txt
rm /tmp/allLibsTemp.txt
#以下两行是为了在QT使用添加，单独使用脚本请注释掉，并且打开49行的提示信息
cat /tmp/lddInfo.txt | tail -n +3 | head -n -1
rm /tmp/lddInfo.txt

