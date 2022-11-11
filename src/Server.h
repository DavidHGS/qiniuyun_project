#pragma once

#include "define.h"
#include "HttpHandler.h"
#include "JsonObject.h"
#include <vector>
#include <map>
#include <mutex>

class Server
{
public:
    Server();
    ~Server();
    void run();                                                         //运行服务器
private:
    void init();                                                        //初始化   
    void dealConnect(int clientFd);                                     //处理到达的连接
    void loginCheck(Json::JsonObject &checkInfo, int client);           //处理登录信息
    void loadUserInfo(const char *fileName);                            //加载用户信息
    void sendMsg(const char *msg, int client, int msgLen = SENDBUFLEN); //向指定客户端发送消息
    void dealItemMsg(const char *msg, int client);                      //处理图元消息
    void back();    //回滚

private:
    int _listenFd;                                  //监听套接字
    std::map<int, const char*> _clientFds;          //存储用于通信的套接字
    std::map<std::string, std::string> _userInfo;   //存储用户信息
    std::vector<Json::JsonObject> _itemStates;      //存储图元状态
    std::mutex _itemStateMutex;                     //访问图元状态信息锁
    HttpHandler _httphandler;                       //处理http消息
};