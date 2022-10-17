#!/bin/bash

if [ $# -eq 0 ];then
	echo "usage: $0 <folder>"
	echo "<folder> should be an absolute path"
	exit 0
fi

folder=${1%/}


function checkDup(){


echo "################################################################" >> ~/Patient/dupLib.txt
echo "$folder目录下重复的动态库" >> ~/Patient/dupLib.txt
date >> ~/Patient/dupLib.txt




find $folder -type f | grep "\.so$\|\.so\." | grep [0-9o]$ >> ~/Patient/allLibsTemp.txt

#去掉白名单的动态库
cat ~/Patient/allLibsTemp.txt | while read Line
do
    str="`cat ~/whiteList.conf | grep -w $Line`"
	if [ -z "$str" ];then
		echo $Line >> ~/Patient/allLibs.txt
	fi
done

cat ~/Patient/allLibs.txt | xargs -n1 md5sum | sort | uniq -w32 --all-repeated=separate >> ~/Patient/dupLib.txt



echo "################################################################" >> ~/Patient/dupLib.txt

#echo "$folder目录下的重复动态库路径存放至~/Patient/dupLib.txt"
}


checkDup
rm ~/Patient/allLibs.txt
rm ~/Patient/allLibsTemp.txt
#shell里执行该脚本请注释以下几行，以及打开注释掉的39行提示信息
cat ~/Patient/dupLib.txt | tail -n +4 | head -n -1 | awk -F ' ' '{print $2}'
rm ~/Patient/dupLib.txt




