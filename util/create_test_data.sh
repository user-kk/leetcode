#!/bin/bash

# 检查是否提供了参数
if [ $# -ne 1 ]; then
    echo "Usage: $0 <filename>.cpp"
    exit 1
fi

# 获取文件名（不包含扩展名）
filename=$(basename "$1" .cpp)


# 创建XX.txt文件
touch "./test/data/${filename}.txt" && code ./test/data/${filename}.txt