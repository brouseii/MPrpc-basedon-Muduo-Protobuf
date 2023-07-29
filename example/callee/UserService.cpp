#include <string>
#include <iostream>

#include "user.pb.h"
#include "user.pb.cc"

#include "MPrpcApplication.h"
#include "MPRpcProvider.h"

/*
    UserService是一个本地服务，提供了两个进程内的本地方法，Login()和Singup()。
*/
class UserService : public fixbug::UserServiceRpc   // 使用在rpc服务发布端（rpc服务提供者）
{
public: 
    bool Login(uint32_t id, string pwd)
    {
        cout << "doing local service: Login()" << endl;
        cout << "userid:"<< id << ", pwd:" << pwd << endl;
        return true;
    }

    /*
        一个Login()方法参与rpc远程调用的调用过程：
        caller ==> Login(LoginRequest) ==> muduo ==> callee ==> Login(LoginRequest) ==> 重写的这个Login方法上
    */ 
    // 重写基类UserServiceRpc的虚函数
    void Login(::google::protobuf::RpcController* controller,
                       const ::fixbug::LoginRequest* request,
                       ::fixbug::LoginResponse* response,
                       ::google::protobuf::Closure* done)
    {
        // 框架给业务上报了反序列化后的请求参数LoginRequest，应用获取相应的数据做本地业务
        uint32_t id = request->id();
        string pwd = request->pwd();

        // 完成本地的的登录业务
        bool login_result = Login(id, pwd);

        // 将响应写入response：{ ResultCode:{ errcode、errmsg }、success }
        fixbug::ResultCode* resultCode = response->mutable_result();
        if (login_result) {
            resultCode->set_errcode(0);
            resultCode->set_errmsg("");
            response->set_success(login_result);
        } else {
            resultCode->set_errcode(1);
            resultCode->set_errmsg("Do Login() failure");
            response->set_success(login_result);
        }

        // 执行回调函数：将响应对象response数据序列化和网络发送，均由框架来完成
        done->Run();
    }

    //////////////////////////////////////////////////////////////////////

    bool Signup(string name, string pwd)
    {
        cout << "doing local service: Signup()" << endl;
        cout << "name:"<< name << ", pwd:" << pwd << endl;
        return true;
    }

    /*
        一个Signup()方法参与rpc远程调用的调用过程：
        caller ==> Signup(SignupRequest) ==> muduo ==> callee ==> Signup(SignupRequest) ==> 重写的这个Signup方法上
    */ 
    // 重写基类UserServiceRpc的虚函数
    void Signup(::google::protobuf::RpcController* controller,
                       const ::fixbug::SignupRequest* request,
                       ::fixbug::SignupResponse* response,
                       ::google::protobuf::Closure* done)
    {
        // 框架给业务上报了反序列化后的请求参数SignupRequest，应用获取相应的数据做本地业务
        string name = request->name();
        string pwd = request->pwd();

        // 完成本地的的业务
        bool signup_result = Signup(name, pwd);

        // 将响应写入response：{ ResultCode:{ errcode、errmsg }、success }
        fixbug::ResultCode* resultCode = response->mutable_result();
        if (signup_result) {
            resultCode->set_errcode(0);
            resultCode->set_errmsg("");
            response->set_success(signup_result);
        } else {
            resultCode->set_errcode(1);
            resultCode->set_errmsg("Do Signup() failure");
            response->set_success(signup_result);
        }

        // 执行回调函数：将响应对象response数据序列化和网络发送，均由框架来完成
        done->Run();
    }
};

int main(int argc, char** argv)
{
    // 调用框架的初始化操作
    MPrpcApplication::Init(argc, argv);

    // provider是一个网络服务对象，将UserService对象发布到rpc节点上
    RpcProvider provider;
    provider.NotifyService(new UserService());

    // 启动一个rpc服务发布节点
    provider.Run();
    // 之后，进程会进入阻塞状态，等待远程的rpc调用请求

    return 0;
}