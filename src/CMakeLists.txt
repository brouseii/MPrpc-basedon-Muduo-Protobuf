# 定义变量，存储当前目录下的所有源文件
aux_source_directory(. SRC_LIST)

# 根据 SRC_LIST 中定义的文件，生成动态库 mprpc
# 注意：这里要链接的muduo库都是静态库，故项目中也需要改为生成静态库（否则项目要生成的动态库链接muduo静态库会失败!!!）
# /usr/local/lib/libmuduo_base.a
# /usr/local/lib/libmuduo_net.a
#add_library(mprpc SHARED ${SRC_LIST})
add_library(mprpc ${SRC_LIST})

# 注意：这里muduo_net必须在muduo_base的前面。zookeeper_mt：多线程版本。
target_link_libraries(mprpc muduo_net muduo_base pthread zookeeper_mt)   