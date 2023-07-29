#include <iostream>
#include <string>
#include <vector>

#include <friend.pb.h>
#include <friend.pb.cc>

#include "MPrpcApplication.h"
#include "MPRpcProvider.h"

/*
    UserService是一个本地服务，提供了两个进程内的本地方法，Login()和Singup()。
*/
class FriendService : public fixbug::FriendServiceRpc   // 使用在rpc服务发布端（rpc服务提供者）
{
public:
    std::vector<std::string> GetFriendLists(uint32_t userid)
    {
        std::cout << "do GetFriendLists() service, userid : [" << userid << "]" << std::endl;
        std::vector<std::string> friendLists;
        friendLists.push_back("li si");
        friendLists.push_back("zhang san");
        return friendLists;
    }

    /*
        一个GetFriendLists()方法参与rpc远程调用的调用过程：
        caller ==> GetFriendLists(GetFriendListsRequest) ==> muduo ==> callee ==> GetFriendLists(GetFriendListsRequest) ==> 重写的这个GetFriendLists方法上
    */ 
    // 重写基类FriendServiceRpc的虚函数
    void GetFriendLists(::google::protobuf::RpcController* controller,
                       const ::fixbug::GetFriendListsRequest* request,
                       ::fixbug::GetFriendListsResponse* response,
                       ::google::protobuf::Closure* done)
    {
        // 框架给业务上报了反序列化后的请求参数GetFriendListsRequest，应用获取相应的数据做本地业务
        uint32_t userid = request->userid(); 

        // 完成本地的的业务
        std::vector<std::string> friendLists = GetFriendLists(userid);

        // 将响应写入response：{ ResultCode:{ errcode、errmsg }、success }
        fixbug::ResultCode* resultCode = response->mutable_result(); 
        resultCode->set_errcode(0);
        resultCode->set_errmsg(""); 
        for (std::string& name : friendLists)
        {
            std::string* namePtr = response->add_friendlists();
            *namePtr = name;
        } 

        // 执行回调函数：将响应对象response数据序列化和网络发送，均由框架来完成
        done->Run();
    }
};

int main(int argc, char** argv)
{
    // 调用框架的初始化操作
    MPrpcApplication::Init(argc, argv);

    // provider是一个网络服务对象，将FriendService对象发布到rpc节点上
    RpcProvider provider;
    provider.NotifyService(new FriendService());

    // 启动一个rpc服务发布节点
    provider.Run();
    // 之后，进程会进入阻塞状态，等待远程的rpc调用请求

    return 0;
}