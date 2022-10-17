#!/bin/bash

if [ $# -eq 0 ];then
	echo "usage: $0 <folder>"
	echo "<folder> should be an absolute path"
	exit 0
fi

#去掉输入参数path的最后一个/
folder=${1%/}

function saveInfo(){

if [ ! -d $folder ];then
	#echo "`date` [INFO] $folder isn't a directory"
	exit 127
fi

find $folder -type f | grep "\.so$\|\.so\." | grep [0-9o]$ >> /tmp/tempAll.txt

#去掉白名单的动态库
if [ -e ~/whiteList.conf ];then
	cat /tmp/tempAll.txt | while read Line
	do
		str="`cat ~/whiteList.conf | grep -w "$Line"`"
		if [ -z "$str" ];then
			echo $Line >> /tmp/allLibs
		fi
	done
fi

cat /tmp/allLibs | awk -F '/' '{print $NF}' | awk -F '.' '{print $1}' | sort | uniq -d | xargs -I{} find $folder -name *{}* | grep "\.so$\|\.so\." | grep [0-9o]$ | xargs md5sum | sort | uniq -w32 | awk '{print $2}' > /tmp/tempFile


#获取有多版本的动态库名字
cat /tmp/tempFile | awk -F '/' '{print $NF}' | awk -F '.' '{print $1}' | sort | uniq -d > /tmp/tempLib

echo "################################################################" >> /tmp/multiVersionLib.txt
echo "$folder目录下存在多版本的动态库" >> /tmp/multiVersionLib.txt
date >> /tmp/multiVersionLib.txt

#从/tmp/tempFile中筛选出来
cat /tmp/tempLib | while read Line
do

	cat /tmp/allLibs | grep -w "$Line" >> /tmp/multiVersionLib.txt
	echo " " >> /tmp/multiVersionLib.txt
done



#cat /tmp/multiVersiontemp.txt | sort | uniq >> /tmp/multiVersionLib.txt
echo "################################################################" >> /tmp/multiVersionLib.txt



#echo "$folder目录下的有多个版本的动态库已存放至/tmp/objFile.txt"

}

saveInfo
rm /tmp/tempFile
rm /tmp/tempLib
rm /tmp/tempAll.txt
rm /tmp/allLibs
#rm /tmp/multiVersiontemp.txt

#shell命令行运行该脚本请注释以下行和打开57行的信息提示
cat /tmp/multiVersionLib.txt | tail -n +4 | head -n -2
rm /tmp/multiVersionLib.txt

