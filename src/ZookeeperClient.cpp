#include "ZookeeperClient.h"
#include "MPrpcApplication.h"

ZookeeperClient::ZookeeperClient() : _zhandle(nullptr)
{ }
ZookeeperClient::~ZookeeperClient()
{
    if (_zhandle != nullptr)
    {   
        // 关闭zk的客户端句柄，并释放资源
        zookeeper_close(_zhandle);
    }
}

// 全局的watcher的观察器：处理zkserver给zkclient的通知
void global_watcher(zhandle_t* zhandle, int type, int state, const char* path, void* watchContext)
{   
    if (type == ZOO_SESSION_EVENT)  // 回调的消息类型是和会话相关的消息类型
    {
        if (state == ZOO_CONNECTED_STATE)   // 表示zkclient和zkserver的连接成功
        {
            sem_t* sem = (sem_t*)zoo_get_context(zhandle); // 给该句柄所在的上下文环境，添加信号量

            // 对value加一，通知ZookeeperClient::Start()所在的线程zkclient已成功连接zkserver
            sem_post(sem);  
        }
    }
}

// 启动zkcli来连接zkserver，“异步连接”过程：通过sem_t信号量来进行线程间通信获取zkclient与zkserver的连接状态
void ZookeeperClient::Start()
{
    std::string hostIP = MPrpcApplication::GetInstance().getMPrpcConfig().Load("zookeeperip");
    std::string hostPort = MPrpcApplication::GetInstance().getMPrpcConfig().Load("zookeeperport");
    std::string hostConnStr = hostIP + ":" + hostPort;

    /*
        // create a handle to used communicate with zookeeper and a zookeeper session that corresponds to that handle. 
        zhandle_t *zookeeper_init(const char *host
                                    , watcher_fn fn
                                    , int recv_timeout
                                    , const clientid_t *clientid
                                    , void *context
                                    , int flags);
        // Session establishment is `asynchronous`, meaning that the session should not be considered established 
        //until (and unless) an event of state `ZOO_CONNECTED_STATE` is received.
    */
    /*
        zookeeper的客户端程序提供了三个线程。
        1. API调用线程。
        2. 网络I/O线程，底层使用poll。    // 用pthread_create()创建
        3. watcher回调线程。             // 用pthread_create()创建
    */
   // 创建zk的客户端句柄
    _zhandle = zookeeper_init(hostConnStr.c_str(), global_watcher, 30000, nullptr, nullptr, 0);
    if (_zhandle == nullptr)
    {
        std::cout << "zookeeper init failure!" << std::endl;
        exit(EXIT_FAILURE);
    }
 
    sem_t sem; // 多进程编程中，信号量是一种用于“同步和互斥访问共享资源”的重要机制
    /*
        sem_init(sem_t *__sem, int __pshared, unsigned int __value)
        1. Initialize semaphore object SEM to VALUE. 
        2. If __pshared != 0 then share it with other processes.
    */
    sem_init(&sem, 0, 0);  
    // 给该句柄所在的上下文环境，添加信号量
    zoo_set_context(_zhandle, &sem);

    // 这里会一直阻塞等待直到value!=0，后执行并对value减一
    sem_wait(&sem); 
    std::cout << "zookeeper init success!" << std::endl;
}

// 在zkserver上，根据指定的path创建znode节点
// state表示节点的状态：{永久性节点（永不删除）、临时性节点（收不到“服务提供者”发送的心跳则删除）}
void ZookeeperClient::Create(const char* path, const char* data, int datalen, int state)
{
    char path_buf[128];
    int buf_len = sizeof(path_buf);

    // Checks the existence of a node in zookeeper `synchronously`.
    int flag = zoo_exists(_zhandle, path, 0, nullptr);
    if (ZNONODE == flag)
    {
        flag = zoo_create(_zhandle, path, data, datalen, &ZOO_OPEN_ACL_UNSAFE, state, path_buf, buf_len);
        if (flag == ZOK) {
            std::cout << "znode create success, path : " << path << std::endl;
        } else {
            std::cout << "flag : " << flag << std::endl;
            std::cout << "znode create failure, path : " << path << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

// 根据参数指定的znode节点的路径，或者znode节点的值
std::string ZookeeperClient::GetData(const char* path)
{
    char buf[128];
    int buf_len = sizeof(buf);
    
    // Gets the data associated with a node `synchronously`.
    int flag = zoo_get(_zhandle, path, 0, buf, &buf_len, nullptr);
    if (flag != ZOK)
    { 
        std::cout << "get znode failure, path : " << path << std::endl;
        return "";        
    } 

    return buf;
} 