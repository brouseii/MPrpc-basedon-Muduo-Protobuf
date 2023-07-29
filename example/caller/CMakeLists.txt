# 变量 SRC_LIST 来存放需要当前目录下的所有源文件
#aux_source_directory(. SRC_LIST)
# 变量 SRC_LIST 来存放需要的源文件
#set(SRC_LIST CallUserRpcService.cpp)
set(SRC_LIST CallFriendRpcService.cpp)  

# 由 SRC_LIST 变量所定义的源文件编译来生成可执行文件 provider
add_executable(consumer ${SRC_LIST})

# 生成可执行文件 provider，需要的库文件
target_link_libraries(consumer mprpc protobuf)