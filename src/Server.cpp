#include "Server.h"
#include "JsonObject.h"
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
    close(_listenFd);
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
    Json::JsonObject json = Json::toJsonObject(machineType.c_str());
    if (json["\"MachineType\""] == WINDOWS)
    {
        _clientFds[clientFd] = WINDOWS;
    }
    else if(json["\"MachineType\""] == WEB)
    {
        _clientFds[clientFd] = WEB;
    }
    else
    {
        LOG("Error: machine type");
        // std::string response;
        // _httphandler.setResponseContent("{\"error_msg\": \"machine_type\"}", response);
        // sendMsg(response.c_str(), clientFd);
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
            // LOG("request: " << msg);
            // std::string response;
            // _httphandler.setResponseContent("\"user\": \"user1\"\n\"password\": \"12345\"", response);
            // sendMsg(response.c_str(), clientFd);
            // LOG(response.c_str());
            if (strlen(msg) > 0)
            {
                Json::JsonObject msgJson = Json::toJsonObject(msg);
                LOG("msgType: " << msgJson["\"msg_type\""]);
                std::string msgType = msgJson["\"msg_type\""];
                if (msgType == MSG_LOGIN)
                {
                    loginCheck(msgJson, clientFd);
                }
                else if(msgType == MSG_ITEM_STATE)
                {
                    dealItemMsg(msg, clientFd);
                }
                else if(msgType == MSG_BACK)
                {
                    back();
                }
            }
        }
        else
        {
            if(errno != EINTR)  //客户端断开连接
            {
                auto it = _clientFds.find(clientFd);
                _clientFds.erase(it);
                LOG("disconnected");
                return;
            }
        }
    }
}

void Server::loginCheck(Json::JsonObject &checkInfo, int client)
{
    if(checkInfo.isEmpty())
    {
        return;
    }
    std::string userName(checkInfo["\"user_name\""]);
    std::string password(checkInfo["\"password\""]);
    // LOG(std::string("username: ") + userName);
    // LOG(std::string("password: ") + password);
    auto it = _userInfo.find(userName);
    Json::JsonObject replyJson;
    replyJson["\"msg_type\""] = MSG_REPLY;
    if (it == _userInfo.end())
    {
        replyJson["\"state\""] = NOUSER;
    }
    else if(it->second != password)
    {
        replyJson["\"state\""] = PSWERROR;
    }
    else if(it->second == password)
    {
        replyJson["\"state\""] = LOGINSUCCESS;
    }
    sendMsg(replyJson.toStr().c_str(), client);
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
    int sendRet = -1;
    if (_clientFds[client] == WINDOWS)
    {
        sendRet = write(client, msg, msgLen);
    }
    else if(_clientFds[client] == WEB)
    {
        HttpHandler handler;
        std::string response;
        handler.setResponseContent(msg, response);
        sendRet = write(client, response.c_str(), msgLen);
    }
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
    Json::JsonObject msgJson = Json::toJsonObject(msg);
    const char *state = msgJson["\"state\""].c_str();
    Json::JsonObject stateJson = Json::toJsonObject(state);
    std::string state_type = stateJson["\"state_type\""];
    _itemStateMutex.lock();
    if (state_type != ITEM_MIDDLE)
    {
        if(state_type == ITEM_BEGIN)
        {
            _itemStates.emplace_back(msgJson);
        }
        else if(state_type == ITEM_END)
        {
            if(_itemStates[_itemStates.size() - 1]["\"state_type\""] == ITEM_BEGIN)
            {
                _itemStates.emplace_back(msgJson);
            }
            else//消息不配对，就抛弃这条消息
            {
                _itemStates.erase(_itemStates.begin() + _itemStates.size() - 1);
            }
        }
    }
    if(_itemStates.size() >= 200)//只保留100条状态信息
    {
        _itemStates.erase(_itemStates.begin(), _itemStates.begin() + 100);
    }
    _itemStateMutex.unlock();
}

void Server::back()
{
    _itemStateMutex.lock();
    if (_itemStates.size() > 0)
    {
        Json::JsonObject msgJson = _itemStates[_itemStates.size() - 2];
        //删除最后一对消息
        _itemStates.erase(_itemStates.begin() + _itemStates.size() - 1);
        _itemStates.erase(_itemStates.begin() + _itemStates.size() - 1);
        //分发
        for(auto it : _clientFds)
        {
            sendMsg(msgJson.toStr().c_str(), it.first);
        }
    }
    _itemStateMutex.unlock();
}