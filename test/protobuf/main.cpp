#include <iostream>
#include "test.pb.h"
using namespace fixbug;
using namespace std;

int main_1()
{
    // 封装了login请求对象的数据
    LoginRequest req_send;
    req_send.set_name("li si");
    req_send.set_pwd("123456");

    // 对象数据序列化 ==> char*
    string send_str;
    if (req_send.SerializeToString(&send_str))
    {
        cout << send_str.c_str() << endl;
    }

    // 根据send_str反序列化一个login请求对象
    LoginRequest req_recv;
    if (req_recv.ParseFromString(send_str))
    {
        cout << req_recv.name() << endl;
        cout << req_recv.pwd() << endl;
    }

    return 0;
}

int main()
{
    LoginResponse login_rsp;
    ErrorMsg* error_msg = login_rsp.mutable_error();
    error_msg->set_error(1);
    error_msg->set_error_msg("login failure!");

    GetFriendListsResponse friend_rsp;
    ErrorMsg *friend_msg = friend_rsp.mutable_error();
    friend_msg->set_error(1);
    friend_msg->set_error_msg("get friend list failure!");

    User* user1 = friend_rsp.add_friendlists();
    user1->set_name("zhang san");
    user1->set_age(20);
    user1->set_sex(User::man);
    
    User* user2 = friend_rsp.add_friendlists();
    user1->set_name("li sa");
    user1->set_age(18);
    user1->set_sex(User::woman);

    cout << "the size of the friendlists: " << friend_rsp.friendlists_size() << endl;

    return 0;
}