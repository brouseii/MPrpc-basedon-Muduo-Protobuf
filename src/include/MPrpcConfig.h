#pragma once

#include <unordered_map>
using namespace std;

// 获取配置文件 configFile:
// zookeeper_ip=***、zookeeper_port=***、rpcserver_port=***、rpcserver_ip=***
class MPrpcConfig
{
public:
    // 负责加载解析配置文件
    void LoadConfigFile(const char* configFile);

    // 查询配置项信息
    string Load(const string& key);
private:
    unordered_map<string, string> _configMap;

    // 去掉字符串前后的空格
    void Trim(string& str);
};
