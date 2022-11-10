#include "Server.h"
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory.h>
#include <thread>
#include <string>
#include <fstream>

#define LOG(s) (std::cout << "Server INFO: " << s << std::endl << std::endl)

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
    _itemStates.clear();
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
            LOG("bind error, error code " << errno);
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
                std::shared_ptr<std::thread> dealThread = std::make_shared<std::thread>(&Server::dealConnect, this, clientFd); //创建线程去处理和客户端的连接
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

    // 判断设备类型
    char *recvBuf = new char[RECVBUFLEN];
    memset(recvBuf, 0, RECVBUFLEN);
    read(clientFd, recvBuf, RECVBUFLEN);
    std::string machineType;
    _httphandler.getRequestContent(recvBuf, machineType);
    if(machineType.c_str() == WINDOWS)
    {
        _clientFds[clientFd] = WINDOWS;
    }
    else if(machineType.c_str() == WEB)
    {
        _clientFds[clientFd] = WEB;
    }
    else
    {
        LOG("undefine machine type");
        return;
    }

    while (1)
    {
        memset(recvBuf, 0, RECVBUFLEN);
        int readLen = read(clientFd, recvBuf, RECVBUFLEN);       
        if(readLen > 0)
        {
            const char *msg = recvBuf;
            if (machineType.c_str() == WEB)
            {
                std::string content;
                _httphandler.getRequestContent(recvBuf, content);
                msg = content.c_str();
            }
            // LOG("http request: " << content);
            // std::string response;
            // _httphandler.setResponseContent("\"user\": \"user1\"\n\"password\": \"12345\"", response);
            // sendMsg(response.c_str(), clientFd);
            if(strlen(msg) > 0)
            {
                char msgType;
                memcpy(&msgType, msg, sizeof(char));
                LOG("msgType: " << msgType);
                if(msgType == MSG_LOGIN)
                {
                    loginCheck(msg + 1, clientFd);
                }
                else if(msgType == MSG_ITEM_STATE)
                {
                    dealItemMsg(msg, clientFd);
                }
            }
        }
        else
        {
            if(errno != EINTR)
            {
                auto it = _clientFds.find(clientFd);
                _clientFds.erase(it);
                LOG("disconnected");
                return;
            }
        }
    }
}

void Server::loginCheck(const char *checkInfo, int client)
{
    if(checkInfo == nullptr)
    {
        return;
    }
    std::string userName(checkInfo);
    std::string password(checkInfo + USERNAMELEN);
    // LOG(std::string("username: ") + userName);
    // LOG(std::string("password: ") + password);
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
        // LOG(userName << ": " << password);
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

void Server::dealItemMsg(const char *msg, int client)
{
    if(msg == nullptr)
    {
        return;
    }
    //将消息分发给当前建立了连接的客户端
    for(auto it : _clientFds)
    {
        if(it.first != client)
        {
            sendMsg(msg, it.first);
        }
    }

    //记录消息
    std::string itemName(msg + 1);
    std::string itemState(msg + ITEMNAMELEN);
    LOG("item name: " << itemName);
    LOG("item state: " << itemState);
    //要去解析state，如果是state_type是b和e，就保存
    if(1)
    {
        
    }
}