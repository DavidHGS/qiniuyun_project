#include "Server.h"
#include "define.h"
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory.h>
#include <thread>
#include <string>

#define LOG(s) (std::cout << "Server INFO: " << s << std::endl)

Server::Server()
{
    LOG("created");
    init();
    loadUserInfo("../data/user.data");
}

Server::~Server()
{
    LOG("delete");
}

void Server::init()
{
    _listenFd = -1;
    _clientFds.clear();
    _userInfo.clear();
}

void Server::run()
{
    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(sockaddr_in));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVERPORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
     _listenFd = socket(AF_INET, SOCK_STREAM, 0);
    if(_listenFd != -1)
    {
        int ret = bind(_listenFd, (sockaddr *)&serverAddr, sizeof(sockaddr));
        if(ret == -1)
        {
            LOG("bind error");
            return;
        }
        listen(_listenFd, 10);
        LOG("start listen");
        while(1)
        {
            sockaddr_in clientInfo;
            socklen_t clientInfoLen = sizeof(sockaddr_in);
            int clientFd = accept(_listenFd, (sockaddr *)&clientInfo, &clientInfoLen);
            if(clientFd != -1)
            {
                LOG(inet_ntoa(clientInfo.sin_addr) << " cnonected");
                _clientFds.emplace_back(clientFd);
                std::shared_ptr<std::thread> dealThread = std::make_shared<std::thread>(&Server::dealConnect, this, clientFd);//创建线程去处理和客户端的连接
                dealThread->detach();//线程自己管理生存周期
            }
        }
        
    }
}

void Server::dealConnect(int clientFd)
{
    if(clientFd == -1)
    {
        return;
    }
    LOG("thread created");
    while(1)
    {
        char *recvBuf = new char[RECVBUFLEN];
        memset(recvBuf, 0, RECVBUFLEN);
        int readLen = read(clientFd, recvBuf, RECVBUFLEN);
        char msgType;
        memcpy(recv, &msgType, sizeof(char));
        if(msgType == 'l')
        {
            loginCheck(recvBuf + 1, clientFd);
        }
        else if(msgType == 's')
        {

        }
    }
}

void Server::loginCheck(const char *checkInfo, int client)
{
    if(checkInfo == nullptr)
    {
        return;
    }
    std::string userName(checkInfo, USERNAMELEN);
    std::string password(checkInfo + USERNAMELEN, PASSWORDLEN);
    LOG(std::string("username: ") + userName);
    LOG(std::string("password: ") + password);
    if(_userInfo.find(userName)->second == password)
    {
        LOG(userName + std::string(" login success"));
        char *sendBuf = new char[SENDBUFLEN];
        char msgType('l');
        const char *msg = "ok";
        memcpy(sendBuf, &msgType, sizeof(char));
        memcpy(sendBuf, msg, strlen(msg) + 1); //要把结束符\0加进去
        sendMsg(sendBuf, client);
    }
}

void Server::loadUserInfo(const char* fileName)
{

}

void Server::sendMsg(const char *msg, int client, int msgLen)
{

}