#pragma once
#include <string>
#include <functional>
#include <unordered_map>

#include "google/protobuf/service.h"
#include "google/protobuf/descriptor.h"

#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>

// 框架提供的用于发布rpc服务的网络对象类
class RpcProvider
{
public:
    // 框架提供给外部发布rpc方法的函数接口
    void NotifyService(google::protobuf::Service* service);

    // 启动rpc服务节点，开始提供rpc远程网络调用服务
    void Run(); 
private:
    muduo::net::EventLoop _loop;   // Muduo-MultiReactor模型中的mainEventLoop

    // service服务类型信息
    struct ServiceInfo
    {
        // 保存服务对象
        google::protobuf::Service* _service;   
        // 保存该服务对象的所有服务方法
        std::unordered_map<std::string, const google::protobuf::MethodDescriptor*> _methodMap; 
    };
    // 保存注册成功的《服务对象》和各自《对应的服务方法》的《所有信息》
    std::unordered_map<std::string, struct ServiceInfo> _serviceMap;

    // 创建的sockfd后的连接/断开事件发生后，执行的回调操作
    void onConnection(const muduo::net::TcpConnectionPtr&);
    // 已建立连接的读写事件发生后，执行的回调操作
    void onMessage(const muduo::net::TcpConnectionPtr&, muduo::net::Buffer*, muduo::Timestamp);

    // Closure的回调操作，用于序列化rpc响应和网络发送
    void SendRpcResponse(const muduo::net::TcpConnectionPtr&, google::protobuf::Message*);
};