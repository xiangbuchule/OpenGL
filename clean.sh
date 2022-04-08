#!/bin/bash
# 该脚本文件所处路径
thisShellFilePath=$(cd "$(dirname "$0")";pwd)
# 记录当前目录路径
nowPath=`pwd`
# 进入该脚本路径
cd "$thisShellFilePath"

# 循环查找目录
deleteAllDictionaries() {
    local sourceDictionary=$1
    local targetDictionary=$2
    local dictionaries=`find $sourceDictionary -type d -name "$targetDictionary"`
    # 如果不为空就删除
    if [[ "$dictionaries" != '' ]];then
        oldIFS=$IFS
        IFS=$'\n'
        for dictionary in $dictionaries
        do
            # 输出删除了那些目录
            echo "delete : $dictionary"
            rm -rf $dictionary
        done
        IFS=$oldIFS
    fi
}
# 只查找一级目录
deleteDictionaries() {
    local sourceDictionary=$1
    local targetDictionary=$2
    local dictionaries=`find $sourceDictionary -maxdepth 1 -type d -name "$targetDictionary"`
    # 如果不为空就删除
    if [[ "$dictionaries" != '' ]];then
        oldIFS=$IFS
        IFS=$'\n'
        for dictionary in $dictionaries
        do
            # 输出删除了那些目录
            echo "delete : $dictionary"
            rm -rf $dictionary
        done
        IFS=$oldIFS
    fi
}

# 获取命令参数
commandParams=$1
# 删除目录
if [[ "$commandParams" == "all" || "$commandParams" == "" ]];then
    deleteAllDictionaries 'LearnOpenGL' 'bin|install'
    deleteDictionaries 'ThirdParty' 'bin'
    deleteDictionaries '.' 'build'
fi
if [[ "$commandParams" == "LearnOpenGL" ]];then
    deleteAllDictionaries 'LearnOpenGL' 'bin|install'
fi
if [[ "$commandParams" == "ThirdParty" ]];then
    deleteAllDictionaries 'LearnOpenGL' 'bin|install'
    deleteDictionaries 'ThirdParty' 'bin'
fi

# cd回去
cd "$nowPath"
