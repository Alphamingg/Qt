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
#检索所有动态库
find $folder -type f | grep "\.so$\|\.so\." | grep [0-9o]$ >> ~/Patient/allLibsTemp.txt

#去掉白名单的动态库
cat ~/Patient/allLibsTemp.txt | while read Line
do
    str="`cat ~/whiteList.conf | grep -w $Line`"
	if [ -z "$str" ];then
		echo $Line >> ~/Patient/allLibs.txt
	fi
done


echo "################################################################" >> ~/Patient/lddInfo.txt
date >> ~/Patient/lddInfo.txt


cat ~/Patient/allLibs.txt | while read Line
do
	isNotFound=`ldd $Line | grep "not found"`
	
	if [ -n "$isNotFound" ];then
		echo $Line >> ~/Patient/lddInfo.txt
		ldd $Line | grep "not found" >> ~/Patient/lddInfo.txt
		echo " " >> ~/Patient/lddInfo.txt
	fi
done


#echo "$folder中所有缺失依赖的动态库已存放~/Patient/lddInfo.txt"
echo "################################################################" >> ~/Patient/lddInfo.txt
}



saveInfo
rm ~/Patient/allLibs.txt
rm ~/Patient/allLibsTemp.txt
#以下两行是为了在QT使用添加，单独使用脚本请注释掉，并且打开46行的提示信息
cat ~/Patient/lddInfo.txt | tail -n +3 | head -n -1
rm ~/Patient/lddInfo.txt

