#include <iostream>
#include <unistd.h> 
#include "MPrpcApplication.h"

MPrpcConfig MPrpcApplication::_mPrpcConfig;

// 获取MPrpcApplication单例
MPrpcApplication& MPrpcApplication::GetInstance()
{
    static MPrpcApplication mPrpcApplication;
    return mPrpcApplication;
}

void showArgsHelp()
{
    cout << "format : command -i <configfile>" << endl;
}

// 负责框架的初始化工作
void MPrpcApplication::Init(int argc, char** argv)
{
    if (argc < 2)
    {
        showArgsHelp();
        exit(EXIT_FAILURE);
    }

    int c = 0;
    string configFile;
    // The getopt() function parses the command-line arguments.
    while ((c = getopt(argc, argv, "i:")) != -1)
    {
        switch (c)
        {
            case 'i':
                configFile = optarg;
                break;
            case '?':
                showArgsHelp();
                exit(EXIT_FAILURE);     
                break;
            case ':':
                showArgsHelp();
                exit(EXIT_FAILURE);        
            default:
                break;
        }
    }

    // 获取配置文件 configFile:
    // zookeeperip=***、zookeeperport=***、rpcserverport=***、rpcserverip=*** 
    _mPrpcConfig.LoadConfigFile(configFile.c_str());

    /*
    std::cout << "rpcserver_ip : " << _mPrpcConfig.Load("rpcserverip") << std::endl;
    std::cout << "rpcserver_port : " << _mPrpcConfig.Load("rpcserverport") << std::endl;
    std::cout << "zookeeper_ip : " << _mPrpcConfig.Load("zookeeperip") << std::endl;
    std::cout << "zookeeper_port : " << _mPrpcConfig.Load("zookeeperport") << std::endl;
    */
}

MPrpcConfig& MPrpcApplication::getMPrpcConfig()
{
    return _mPrpcConfig;
}
