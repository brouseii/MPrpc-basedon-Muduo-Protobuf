#include "MPrpcApplication.h"
#include "MPrpcChannel.h"
#include "RpcHeader.pb.h"
#include "MPrpcController.h"
#include "ZookeeperClient.h"

#include <unistd.h>
#include <sys/types.h>   
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <errno.h> 

#define BUF_SIZE 1024

/*
    rpc网络传输的字符流的格式：header_size + header_str:{service_name、method_name、args_size} + args
*/
/* 所有通过stub代理对象调用的rpc方法，都会通过这里统一做rpc方法调用的数据序列化和网络发送 */
void MPrpcChannel::CallMethod(const google::protobuf::MethodDescriptor* method
                    , google::protobuf::RpcController* controller
                    , const google::protobuf::Message* request
                    , google::protobuf::Message* response
                    , google::protobuf::Closure* done)
{
    const google::protobuf::ServiceDescriptor* service = method->service();
    std::string service_name = service->name();  // service_name
    std::string method_name = method->name();    // method_name

    // 获取参数的序列化字符串长度
    uint32_t args_size = 0;
    std::string args_str;
    if (request->SerializeToString(&args_str)) {
        args_size = args_str.size();
    } else {
        controller->SetFailed("serialize the rpc args of request failure!");
        return;
    }

    // 获取rpc请求的header
    mprpc::RpcHeader rpcHeader;
    rpcHeader.set_service_name(service_name);
    rpcHeader.set_method_name(method_name);
    rpcHeader.set_args_size(args_size);

    uint32_t header_size = 0;
    std::string rpc_header_str;
    if (rpcHeader.SerializeToString(&rpc_header_str)) {
        header_size = rpc_header_str.size();
    } else {
        controller->SetFailed("serialize the rpc head of request failure!");
        return;
    }

    // 整合待发送的rpc请求的字符串
    // rpc网络传输的字符流的格式：header_size + header_str:{service_name、method_name、args_size} + args
    std::string sendCharStream;
    /*
        template<typename _CharT, typename _Traits, typename _Alloc>
        basic_string<_CharT, _Traits, _Alloc>& basic_string<_CharT, _Traits, _Alloc>::insert(
            size_type __pos
            , const _CharT* __s
            , size_type __n)
    */
    sendCharStream.insert(0, (char*)&header_size, 4);  // header_size
    sendCharStream += rpc_header_str;                               // header_str:{service_name、method_name、args_size}
    sendCharStream += args_str;                                     // args

    std::cout << "................ sendCharStream : " << sendCharStream << " ................" << std::endl;
    std::cout << "................ header_size : " << header_size << " ................" << std::endl;
    std::cout << "rpc_head_str : " << rpc_header_str << ", { service_name : " << service_name << ", method_name : " << method_name << ", args_size : " << args_size << "} ................" << std::endl;
    std::cout << "................ args_str : " << args_str << " ................" << std::endl;

    ////////////////////////////////////////////////////////////////////////////////

    /* 使用tcp编程（无需高并发故不需要使用muduo网络库），完成请求rpc方法的远程调用 */
    /*
       #include <sys/types.h>   
       #include <sys/socket.h>
       int socket(int domain, int type, int protocol);
    */
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd == -1)
    {
        controller->SetFailed("create socket failure, " + to_string(errno) + "!");
        return;  
    }

    /*
        // 封装配置文件中rpc服务的ip和port
        std::string ip = MPrpcApplication::GetInstance().getMPrpcConfig().Load("rpcserverip");
        uint16_t port = atoi(MPrpcApplication::GetInstance().getMPrpcConfig().Load("rpcserverport").c_str());
    */
    // rpc调用方想要调用service_name的method_name服务，则需要查询zookeeper上该服务所在的host信息{ip:port}
    ZookeeperClient zkClient;
    zkClient.Start();
    std::string method_path = "/" + service_name + "/" + method_name;
    std::string host_data = zkClient.GetData(method_path.c_str());
    if (host_data == "") 
    {
        controller->SetFailed("zookeeper don't have " + method_path + "!");
        return;
    } 
    int idx = host_data.find(":");
    if (idx == -1)
    {
        controller->SetFailed(method_path + " whom zookeeper have found is failure!");
        return;        
    }
    std::string ip = host_data.substr(0, idx);
    uint16_t port = atoi(host_data.substr(idx + 1, host_data.size() - idx).c_str());

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());

    // 连接rpc的ip:port服务节点并发送数据
    if (connect(clientfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    { 
        controller->SetFailed("connect failure, " + to_string(errno) + "!");
        close(clientfd);
        return; 
    }
    
    // 发送rpc请求
    std::string& send_rpc_str = sendCharStream;
    if (send(clientfd, send_rpc_str.c_str(), send_rpc_str.size(), 0) == -1)
    { 
        controller->SetFailed("send failure, " + to_string(errno) + "!");
        close(clientfd);
        return;
    }

    ////////////////////////////////////////////////////////////////////////////////

    // 接收rpc请求的响应值
    char recv_buf[1024] = {0}; int recv_size = 0;
    if ((recv_size = recv(clientfd, recv_buf, BUF_SIZE, 0)) == -1)
    { 
        controller->SetFailed("receive failure, " + to_string(errno) + "!");
        close(clientfd);
        return;
    }

    // 反序列化recv_buf中的响应数据，并传给response
    if (!response->ParseFromArray(recv_buf, recv_size))
    { 
        controller->SetFailed("parse failure, response_str:" + string(recv_buf) + "!");
        close(clientfd);
        return;
    }
    
    close(clientfd);
}