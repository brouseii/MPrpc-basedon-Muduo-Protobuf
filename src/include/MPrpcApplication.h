#pragma once
#include "MPrpcConfig.h"

// mprpc框架的基础类
class MPrpcApplication
{
public:
    // 获取MPrpcApplication单例
    static MPrpcApplication& GetInstance();
    
    // 负责框架的初始化工作
    static void Init(int argc, char** argv);

    static MPrpcConfig& getMPrpcConfig();
private:
    static MPrpcConfig _mPrpcConfig;

    /* 采用单例模式 */
    MPrpcApplication() {}
    // 禁用拷贝构造函数和移动拷贝构造函数
    MPrpcApplication(const MPrpcApplication&) = delete;
    MPrpcApplication(MPrpcApplication&&) = delete; 
};
