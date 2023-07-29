# 变量 SRC_LIST 来存放需要的源文件
#set(SRC_LIST UserService.cpp)
set(SRC_LIST FriendService.cpp)

# 由 SRC_LIST 变量所定义的源文件编译来生成可执行文件 provider
add_executable(provider ${SRC_LIST})

# 生成可执行文件 provider，需要的库文件
target_link_libraries(provider mprpc protobuf)