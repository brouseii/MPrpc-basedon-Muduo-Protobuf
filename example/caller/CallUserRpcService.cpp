#include <iostream>
#include "MPrpcApplication.h" 
#include "MPrpcChannel.h"

#include "user.pb.cc"

int main(int argc, char** argv)
{
    // 想要使用mprpc框架提供的rpc服务调用，就必须先调用框架的初始化函数
    // 注：只需初始化一次即可。
    MPrpcApplication::Init(argc, argv);

    // 调用远程发布的rpc方法：如Login()方法
    fixbug::UserServiceRpc_Stub stub(new MPrpcChannel());  // MPrpcChannel::callMethod()，集中来做所有rpc方法调用的参数序列化和网络发送
    /*
        父类中定义了虚函数virtual void google::protobuf::RpcChannel::callMethod()，子类MPrpcChannel进行了重写
        这里new了一个派生类MPrpcChannel对象，赋值给了父类指针google::protobuf::RpcChannel*，即“父类指针指向了子类对象”
    */

    /////////////////////////////  rpc Login()  /////////////////////////////////
    // rpc调用的方法请求参数
    fixbug::LoginRequest loginRequest;
    loginRequest.set_id(1);
    loginRequest.set_pwd("123456");

    // rpc调用的方法响应参数
    fixbug::LoginResponse loginresponse;

    // 发起rpc方法的调用
    /* 
        Login(::google::protobuf::RpcController* controller,
            const ::fixbug::LoginRequest* request,
            ::fixbug::LoginResponse* response,
            ::google::protobuf::Closure* done)
    */
    MPrpcController controller;  // 反应调用rpc方法过程中的一些状态信息
    stub.Login(&controller, &loginRequest, &loginresponse, nullptr);   
    // 最终调用的是：RpcChannel::callMethod ==> MPrpcChannel::callMethod()，集中来做所有rpc方法调用的参数序列化和网络发送

    // 一次rpc调用完成，读取返回的结果 
    if (controller.Failed())
    {
        std::cout << controller.ErrorText() << std::endl;
    } 
    else 
    {
        if (loginresponse.result().errcode() == 0) {
            std::cout << "rpc Login response successfully, " << loginresponse.success() << "." << std::endl; 
        } else {
            std::cout << "rpc Login reponse failure, " << loginresponse.result().errmsg() << "!" << std::endl;
        }
    }

    /////////////////////////////  rpc Signup()  /////////////////////////////////
    // rpc调用的方法请求参数
    fixbug::SignupRequest signupRequest;
    signupRequest.set_name("li si");
    signupRequest.set_pwd("123456");

    // rpc调用的方法响应参数
    fixbug::SignupResponse signupResponse;

    // 发起rpc方法的调用
    /* 
        Signup(::google::protobuf::RpcController* controller,
            const ::fixbug::LoginRequest* request,
            ::fixbug::LoginResponse* response,
            ::google::protobuf::Closure* done)
    */
    stub.Signup(nullptr, &signupRequest, &signupResponse, nullptr);   
    // 最终调用的是：RpcChannel::callMethod ==> MPrpcChannel::callMethod()，集中来做所有rpc方法调用的参数序列化和网络发送

    // 一次rpc调用完成，读取返回的结果
    if (controller.Failed())
    {
        std::cout << controller.ErrorText() << std::endl;
    } 
    else 
    {
        if (signupResponse.result().errcode() == 0) {
            std::cout << "rpc Signup response successfully, " << signupResponse.success() << "." << std::endl; 
        } else {
            std::cout << "rpc Signup reponse failure, " << signupResponse.result().errmsg() << "!" << std::endl;
        }
    }

    return 0;
}