#pragma once
#include <google/protobuf/stubs/common.h>  
#include <google/protobuf/service.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>

// 控制程序执行的状态
class MPrpcController : public google::protobuf::RpcController
{
public:
    MPrpcController();
    void Reset();
    bool Failed() const;
    std::string ErrorText() const;
    void SetFailed(const std::string& reason);

    // 目前尚未实现
    void StartCancel();
    bool IsCanceled() const;

    void NotifyOnCancel(google::protobuf::Closure* callback);
private:
    bool _failed;           // RPC方法执行过程中的状态
    std::string _errText;   // RPC方法执行过程中的错误信息 
};