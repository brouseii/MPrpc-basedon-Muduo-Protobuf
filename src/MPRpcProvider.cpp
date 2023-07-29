#include "MPRpcProvider.h"
#include "MPrpcApplication.h"
#include "RpcHeader.pb.h"
#include "ZookeeperClient.h"

#define ZNODE_ASSOCIATIONDATA_LEN 128

// 框架提供给外部发布rpc方法的函数接口
void RpcProvider::NotifyService(google::protobuf::Service* service)
{
    // service服务类型的信息
    ServiceInfo serviceInfo;
    serviceInfo._service = service;

    // 获取了service服务类型对象的描述信息
    const google::protobuf::ServiceDescriptor* serviceDescriptorPtr = service->GetDescriptor();
    std::cout << "service name : " << serviceDescriptorPtr->name() << std::endl;

    // 获取服务对象service的方法的数量
    int methodCnt = serviceDescriptorPtr->method_count();
    for (int i = 0; i < methodCnt; ++i)
    {
        // 获取服务对象指定下标的服务方法的“抽象描述”
        const google::protobuf::MethodDescriptor* methodDescriptorPtr = serviceDescriptorPtr->method(i); 
        std::cout << "method name : " << methodDescriptorPtr->name() << std::endl;

        // _mthodMap中，存储着《方法名，方法描述符指针》
        serviceInfo._methodMap.insert({ methodDescriptorPtr->name(), methodDescriptorPtr });
    }

    // _serviceMap中，存储着《服务名，服务类型的详细信息》
    _serviceMap.insert({ serviceDescriptorPtr->name(), serviceInfo });
}

// 启动rpc服务节点，开始提供rpc远程网络调用服务
void RpcProvider::Run()
{
    // 封装配置文件中rpc服务的ip和port
    string ip = MPrpcApplication::GetInstance().getMPrpcConfig().Load("rpcserverip");
    uint16_t port = atoi(MPrpcApplication::GetInstance().getMPrpcConfig().Load("rpcserverport").c_str());
    muduo::net::InetAddress addr(ip, port);
    
    // 创建TcpServer对象
    muduo::net::TcpServer tcpServer(&_loop, addr, "RpcProvider");
    // 注册：连接/断开回调、读写回调函数
    tcpServer.setConnectionCallback(std::bind(&RpcProvider::onConnection, this, std::placeholders::_1));
    tcpServer.setMessageCallback(std::bind(&RpcProvider::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    // 设置Muduo底层开启的线程数 
    tcpServer.setThreadNum(4);   /* One Loop Per Thread && threadNum:4   ===>   一个mainEventLoop、三个subEventLoop */

    // 将当前rpc节点上要发布的服务全部注册到zk上，让rpc client可以从zk上发现服务
    // zookeeper的客户端程序提供了三个线程：API调用线程、网络I/O线程、watcher回调线程。       
    //其中，zkClient的网络IO线程会在1/3timeout时间发送ping心跳包给zkServer，来告知其自己还存在。
    ZookeeperClient zkClient;
    zkClient.Start();
    // service_name为永久性节点，method_name为临时节点
    for (auto& service : _serviceMap)
    {
        // path ==> `/service_name`
        std::string service_path = "/" + service.first;
        zkClient.Create(service_path.c_str(), nullptr, 0);  // state=0，表示service_name为永久性节点
        for (auto& method : service.second._methodMap)
        {
            // path ==> `/service_name/method_name`
            std::string method_path = service_path + "/" + method.first;
            char method_path_associationData[ZNODE_ASSOCIATIONDATA_LEN] = {0};
            sprintf(method_path_associationData, "%s:%d", ip.c_str(), port);
            zkClient.Create(method_path.c_str(), method_path_associationData, strlen(method_path_associationData), ZOO_EPHEMERAL);   // state=ZOO_EPHEMERAL，表示method_name为临时节点
        }
    }

    // 启动网络服务并开启mainLoop的事件循环
    std::cout << "RpcServer start service at " << ip << ":" << port << "." << endl;
    tcpServer.start();
    _loop.loop();
}

// 创建的sockfd后的连接/断开事件发生后，执行的回调操作
void RpcProvider::onConnection(const muduo::net::TcpConnectionPtr& conn)
{
    if (!conn->connected())
    {
        // 将rpc的callee与caller断开
        conn->shutdown();   
    }
}
/*
    框架内部，RpcProvider和RpcConsumer协商好，相互之间通信的protobuf数据类型。
    serviceName、methodName、args
    定义proto的message类型`RpcHeader : {serviceName, methodName, args_size}`，进行数据的序列化和反序列化
    网路中传输的字符流：`header_size（4bytes）+ head_str + args_str`
*/
// 已建立连接的读写事件发生后，执行的回调操作
// 如果远程有一个rpc服务的调用请求，那么onMessage方法就会响应
void RpcProvider::onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp time)
{
    // 接收远程rpc请求的字符流
    std::string recvCharStream = buf->retrieveAllAsString();

    /* 网路中传输的字符流：`header_size（4bytes）+ head_str + args_str` */
    // 1. 从字符流中，读取前四个字节的内容做为`header_size（4bytes）`
    uint32_t header_size = 0;
    recvCharStream.copy((char*)&header_size, 4, 0);
    std::string rpc_header_str = recvCharStream.substr(4, header_size);
    
    // 2. 反序列化 rpc_header_str 数据，得到rpc请求的详细信息：service_name、method_name、args_size
    /* message类型`RpcHeader : {service_name, method_name, args_size}` */
    mprpc::RpcHeader rpcHeader;      
    string service_name, method_name; uint32_t args_size;
    if (rpcHeader.ParseFromString(rpc_header_str)) {
        // 数据反序列化成功
        service_name = rpcHeader.service_name();
        method_name = rpcHeader.method_name();
        args_size = rpcHeader.args_size();
    } else {
        std::cout << "rpc_header_str : " << rpc_header_str << "parse failure!" << std::endl;
    }

    // 3. 获取rpc方法参数的字符流数据
    std::string args_str = recvCharStream.substr(4 + header_size, args_size);

    std::cout << "................ recvCharStream : " << recvCharStream << " ................" << std::endl;
    std::cout << "................ header_size : " << header_size << " ................" << std::endl;
    std::cout << "rpc_head_str : " << rpc_header_str << ", { service_name : " << service_name << ", method_name : " << method_name << ", args_size : " << args_size << "} ................" << std::endl;
    std::cout << "................ args_str : " << args_str << " ................" << std::endl;

    ////////////////////////////////////////////////////////////////////////////////

    // 获取service对象和method对象
    auto serviceIter = _serviceMap.find(service_name);
    if (serviceIter == _serviceMap.end())
    {
        std::cout << service_name << " is non-exist!" << endl;
    }
    google::protobuf::Service* service = serviceIter->second._service;      // 获取service对象

    auto methodIter = serviceIter->second._methodMap.find(method_name);
    if (methodIter == serviceIter->second._methodMap.end())
    {
        std::cout << service_name << "::" << method_name << " is non-exist!" << endl;
    } 
    const google::protobuf::MethodDescriptor* method = methodIter->second;  // 获取method对象

    //  生成rpc方法调用的请求和响应 ==> 请求`const ::fixbug::LoginRequest*`和响应`::fixbug::LoginResponse*`
    google::protobuf::Message* request = service->GetRequestPrototype(method).New();
    if (!request->ParseFromString(args_str))
    {
        std::cout << "Request parse failure!" << std::endl;
        return;
    }
    google::protobuf::Message* response = service->GetResponsePrototype(method).New();

    // 给下面method方法，绑定的Closure回调函数
    google::protobuf::Closure* done = google::protobuf::NewCallback<RpcProvider
                                                                    , const muduo::net::TcpConnectionPtr&
                                                                    , google::protobuf::Message*>(this
                                                                                                , &RpcProvider::SendRpcResponse
                                                                                                , conn, response);
    // 在框架上，根据远端rpc请求，调用当前rpc节点上发布的方法
    service->CallMethod(method, nullptr, request, response, done);
}   

// Closure的回调操作，用于序列化rpc响应和网络发送
void RpcProvider::SendRpcResponse(const muduo::net::TcpConnectionPtr& conn, google::protobuf::Message* response)
{
    std::string response_str;
    if (response->SerializeToString(&response_str)) {
        // 序列化后，将rpc方法的执行结果通过网络发送给rpc的调用方
        conn->send(response_str); 
    } else {
        std::cout << "Response serialize failure!" << std::endl;
    }
    conn->shutdown();   // 模拟http的“短连接”服务，由RpcProvider主动断开连接
}