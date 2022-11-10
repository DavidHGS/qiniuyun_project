#pragma once

#include "define.h"
#include <vector>
#include <map>
#include <mutex>

class Server
{
public:
    Server();
    ~Server();
    void run();     //运行服务器
private:
    void init();    //初始化   
    void dealConnect(int clientFd);     //处理到达的连接
    void loginCheck(const char *checkInfo, int client);     //处理登录信息
    void loadUserInfo(const char *fileName);     //加载用户信息
    void sendMsg(const char *msg, int client, int msgLen = SENDBUFLEN); //向指定客户端发送消息
    void dealItemMsg(const char *msg, int client);      //处理图元消息
    
private:
    int _listenFd;      //监听套接字
    std::vector<int> _clientFds;    //存储用于通信的套接字
    std::map<std::string, std::string> _userInfo;   //存储用户信息
    std::vector<std::string> _itemStates;
    std::mutex _itemStateMutex;
};