#!/bin/bash

set -e

# 编译
rm -rf `pwd`/build/*
cd `pwd`/build/ && cmake .. && make
cd ..

# 把头文件拷贝到 /usr/include/MPrpc  
if [ ! -d /usr/include/MPrpc ]; then 
    mkdir /usr/include/MPrpc
fi

cd `pwd`/src/include/
for header in `ls *.hpp`
do
    cp $header /usr/include/MPrpc
done
for header in `ls *.h`
do
    cp $header /usr/include/MPrpc
done
cd ..
cd ..

# 生成的静态库拷贝到 /usr/lib  
cp `pwd`/lib/libmprpc.a /usr/lib

# 刷新链接库的缓存
ldconfig