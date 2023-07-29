#include "MPrpcController.h"

MPrpcController::MPrpcController()
{
    _failed = false;
    _errText = "";
}

void MPrpcController::Reset()
{
    _failed = false;
    _errText = "";    
}

bool MPrpcController::Failed() const
{
    return _failed;
}

std::string MPrpcController::ErrorText() const
{
    return _errText;
}

void MPrpcController::SetFailed(const std::string& reason)
{
    _failed = true;
    _errText = reason;
}

// 目前尚未实现
void MPrpcController::StartCancel() 
{ }

bool MPrpcController::IsCanceled() const
{
    return false;
}

void MPrpcController::NotifyOnCancel(google::protobuf::Closure* callback)
{ }