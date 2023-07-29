#include <iostream>
#include "MPrpcApplication.h" 
#include "MPrpcChannel.h"
#include "MPrpcController.h"

#include "friend.pb.cc"

int main(int argc, char** argv)
{
    // 想要使用mprpc框架提供的rpc服务调用，就必须先调用框架的初始化函数
    // 注：只需初始化一次即可。
    MPrpcApplication::Init(argc, argv);

    // 调用远程发布的rpc方法：如Login()方法
    fixbug::FriendServiceRpc_Stub stub(new MPrpcChannel());  // MPrpcChannel::callMethod()，集中来做所有rpc方法调用的参数序列化和网络发送
    /*
        父类中定义了虚函数virtual void google::protobuf::RpcChannel::callMethod()，子类MPrpcChannel进行了重写
        这里new了一个派生类MPrpcChannel对象，赋值给了父类指针google::protobuf::RpcChannel*，即“父类指针指向了子类对象”
    */

    /////////////////////////////  rpc GetFriendLists()  /////////////////////////////////
    // rpc调用的方法请求参数
    fixbug::GetFriendListsRequest getFriendListsRequest;
    getFriendListsRequest.set_userid(1);

    // rpc调用的方法响应参数
    fixbug::GetFriendListsResponse getFriendListsResponse;

    // 发起rpc方法的调用:
    /* 
        GetFriendLists(::google::protobuf::RpcController* controller,
            const ::fixbug::GetFriendListsRequest* request,
            ::fixbug::GetFriendListsResponse* response,
            ::google::protobuf::Closure* done)
    */ 
    MPrpcController controller;  // 反应调用rpc方法过程中的一些状态信息
    stub.GetFriendLists(&controller, &getFriendListsRequest, &getFriendListsResponse, nullptr);   
    // 最终调用的是：RpcChannel::callMethod ==> MPrpcChannel::callMethod()，集中来做所有rpc方法调用的参数序列化和网络发送

    // 一次rpc调用完成，读取返回的结果
    if (controller.Failed())
    {
        std::cout << controller.ErrorText() << std::endl;
    } 
    else 
    {
        if (getFriendListsResponse.result().errcode() == 0) {
            std::cout << "rpc GetFriendLists response successfully." << std::endl; 
            for (int i = 0; i < getFriendListsResponse.friendlists_size(); ++i)
            {
                std::cout << getFriendListsResponse.friendlists(i) << std:: endl;
            }
        } else {
            std::cout << "rpc GetFriendLists reponse failure, " << getFriendListsResponse.result().errmsg() << "!" << std::endl;
        }
    }
 
    return 0;
}