#pragma once
 
#include "LockQueue.hpp"

enum LogLevel
{       
    INFO,   // 普通信息
    ERROR,  // 错误信息
};

#define LOG_LEN 1024

// MPrpc框架提供的日志系统
class Logger
{
public: 
    // 获取Logger单例
    static Logger& GetInstance();
     
    // 设置日志级别
    void SetLogLevel(LogLevel logLevel);

    // 将日志写入_lockQueue日志缓冲队列中
    void Log(std::string msg);
private:
    int _logLevel;   // 记录日志级别
    LockQueue<std::string> _lockQueue;   // 日志缓冲队列

    /* 采用单例模式 */
    // 开启写日志线程
    Logger();
    // 禁用拷贝构造函数和移动拷贝构造函数
    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
};


#define LOG_INFO(logmsgformat, ...) do { \
        Logger& logger = Logger::GetInstance(); \
        logger.SetLogLevel(INFO); \ 
        char log[LOG_LEN] = {0}; \
        snprintf(log, LOG_LEN, logmsgformat, ##__VA_ARGS__); \
        logger.Log(log); \ 
    } while(0)
#define LOG_ERROR(logmsgformat, ...) do { \
        Logger& logger = Logger::GetInstance(); \
        logger.SetLogLevel(ERROR); \ 
        char log[LOG_LEN] = {0}; \
        snprintf(log, LOG_LEN, logmsgformat, ##__VA_ARGS__); \
        logger.Log(log); \ 
    } while(0)