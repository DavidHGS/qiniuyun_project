#include "Server.h"
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory.h>
#include <thread>
#include <string>
#include <fstream>

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
        memcpy(recvBuf, &msgType, sizeof(char));
        if(msgType == MSG_LOGIN)
        {
            loginCheck(recvBuf + 1, clientFd);
        }
        else if(msgType == MSG_ITEM_STATE)
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
    auto it = _userInfo.find(userName);
    char *sendBuf = new char[SENDBUFLEN];
    memcpy(sendBuf, &MSG_REPLY, sizeof(char));
    if(it == _userInfo.end())
    {
        LOG(userName + std::string(" no user"));  
        memcpy(sendBuf + 1, &NOUSER, sizeof(short int));
    }
    else if(it->second != password)
    {
        LOG(userName + std::string(" password error"));  
        memcpy(sendBuf + 1, &PSWERROR, sizeof(short int)); 
    }
    else if(it->second == password)
    {
        LOG(userName + std::string(" login success"));  
        memcpy(sendBuf + 1, &LOGINSUCCESS, sizeof(short int)); 
    }
    sendMsg(sendBuf, client);
    delete [] sendBuf;
}

void Server::loadUserInfo(const char* fileName)
{
    std::ifstream fileHandle(fileName, std::ios::in);
    if(!fileHandle.is_open())
    {
        LOG("user file open failed");
        return;
    }
    while(!fileHandle.eof())
    {
        std::string userName ;
        std::string password;
        fileHandle >> userName >> password;
        _userInfo[userName] = password;
        LOG(userName << ": " << password);
    }
}

void Server::sendMsg(const char *msg, int client, int msgLen)
{
    if(msg == nullptr)
    {
        return;
    }
    if(client == -1)
    {
        return;
    }
    int sendRet = write(client, msg, msgLen);
    if(sendRet == -1)
    {
        LOG("send failed, error code : " << errno);
    }
}