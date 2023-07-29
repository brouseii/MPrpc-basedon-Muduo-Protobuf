#pragma once

#include <queue>
#include <thread>
#include <mutex>               // pthread_mutex_t
#include <condition_variable>  // pthread_condition_t

/*
    “异步”写日志的日志队列：
    所谓的 “异步”，指会如下两个操作分别在不同的线程中，
    1）MPrpc框架中的Muduo网络库中高并发时，多个worker线程会争夺给_queue中写日志；
    2）另一个独立的“写日志线程”，会将_queue中的日志写入文件中；
*/
template<typename T>
class LockQueue
{
public:
    // MPrpc框架中的Muduo网络库中，高并发时会有多个worker线程争夺给_queue中写日志
    void Push(const T& data)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _queue.push(data);
        // 一旦缓冲队列_queue中有数据，就会通知_conditionVar对wait状态的锁重新加锁
        _conditionVar.notify_one();
    }

    // 只有一个写日志线程，会从_queue中的不断取出日志记录，并写入文件中（在Logger::Logger()中执行）
    T Pop()
    {
        std::unique_lock<std::mutex> lock(_mutex);
        while (_queue.empty())
        {
            // 日志队列为空，写日志线程（即本线程）进入wait状态
            _conditionVar.wait(lock);  
            // wait() 会释放 mutex,直到被 notify 或者 notify_all 通知后才会重新加锁，并继续执行本线程
        }

        T data = _queue.front();
        _queue.pop();
        return data;
    }
    std::queue<T> _queue;
    std::mutex _mutex;
    std::condition_variable _conditionVar;
};