#pragma once

#include <iostream>
#include <string>
#include <semaphore.h>
#include <zookeeper/zookeeper.h>

// 封装的zookeeper客户端类
class ZookeeperClient
{
public:
    ZookeeperClient();
    ~ZookeeperClient();

    // 启动zkCli来连接zkserver
    void Start();

    // 在zkserver上，根据指定的path创建znode节点
    void Create(const char* path, const char* data, int datalen, int state = 0);

    // 根据参数指定的znode节点的路径，或者znode节点的值
    std::string GetData(const char* path);
private:
    // zk的客户端句柄
    zhandle_t* _zhandle;
};