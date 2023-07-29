#include "Logger.h"
#include <time.h>
#include <iostream>

// 获取Logger单例
Logger& Logger::GetInstance()
{
    static Logger logger;
    return logger;
}

// 写日志线程（只有一个），会将_lockQueue中的日志记录写入文件中
Logger::Logger()
{
    std::thread writeLogTask([&]() {
        for (;;)
        {
            // 获取当前的日期，之后取日志信息，并追加到相应的日志文件中
            time_t now = time(nullptr);
            tm* nowtm = localtime(&now);

            char filename[128];
            sprintf(filename, "%d-%d-%d-log.txt", nowtm->tm_year + 1900, nowtm->tm_mon + 1, nowtm->tm_mday);

            FILE* pf = fopen(filename, "a+");
            if (pf == nullptr)
            {
                std::cout << "logger file [" << filename << "] open failure!" << std::endl;
                exit(EXIT_FAILURE);
            } 

            // 从日志缓冲队列_lockQueue中获取一条日志记录log
            std::string log = _lockQueue.Pop();
            char time_buf[128] = {0};   // 给该条日志记录加上时间前缀time_buf
            sprintf(time_buf, "%d:%d:%d [%s] ", nowtm->tm_hour, nowtm->tm_min, nowtm->tm_sec, (_logLevel == INFO ? "INFO" : "ERROR"));
            log.insert(0, time_buf);
            // 将从_lockQueue中获取的加了时间前缀的日志记录log，写入当前的日志文件filename中
            fputs((const char*)log.c_str(), pf);

            // 关闭日志文件
            fclose(pf);
        }
    });
    writeLogTask.detach();   // 设置线程为“分离状态”，即为守护线程
}

// 设置日志级别
void Logger::SetLogLevel(LogLevel logLevel)
{
    _logLevel = logLevel;
}

// 将日志写入_lockQueue日志缓冲队列中
void Logger::Log(std::string msg)
{
    _lockQueue.Push(msg);
}