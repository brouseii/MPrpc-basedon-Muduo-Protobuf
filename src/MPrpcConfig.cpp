#include "MPrpcConfig.h"
#include <iostream>
#define BUF_SIZE 512

// 负责加载解析配置文件
void MPrpcConfig::LoadConfigFile(const char* configFile)
{   
    FILE* fileptr = fopen(configFile, "r");
    if (fileptr == nullptr)
    {
        std::cout << configFile << " is note exist!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // 一行一行操作：去掉注释、读取=后的配置项、去掉每行的前后多余的空格
    while (!feof(fileptr))
    {
        char buf[BUF_SIZE] = {0};
        fgets(buf, BUF_SIZE, fileptr);

        string conf_(buf);
        // 去掉字符串前/后多余的空格
        this->Trim(conf_);

        // 跳过注释和空行
        if (conf_[0] == '#' || conf_.empty())
        {
            continue;
        }

        // 解析配置项
        int idx =  conf_.find('=');
        if (idx == -1)  // 配置项所在的行格式不合法
        {
            continue;
        }

        // 获取配置项，并存放在_configMap中
        string key = conf_.substr(0, idx);
        // 避免出现这种`rpcserverip   =127.0.0.1`，即等号前面有空格
        this->Trim(key);

        // 避免出现这种`rpcserverip=127.0.0.1\n`
        int endidx = conf_.find('\n', idx); 
        string value = conf_.substr(idx + 1, endidx - idx - 1);
        // 避免出现这种`rpcserverip=   127.0.0.1`，即等号后面有空格
        this->Trim(value);
        _configMap[key] = value;
    }
}

// 查询配置项信息
string MPrpcConfig::Load(const string& key)
{
    if (_configMap.find(key) == _configMap.end())
    {
        return string();
    }
    return _configMap[key];
}

// 去掉字符串前后的空格
void MPrpcConfig::Trim(string& str)
{
    int idx = str.find_first_not_of(' ');
    if (idx != -1)
    {
        str = str.substr(idx, str.size() - idx);
    }

    idx = str.find_last_not_of(' ');
    if (idx != -1)
    {
        str = str.substr(0, idx + 1);
    }
}