#include "../src/define.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <iostream>

class Client
{
public:
    Client(const char * serverIp, in_port_t serverPort) : _serverIp(serverIp), _serverPort(serverPort)
    {
        init();
    }
    void init()
    {
        _clientFd = socket(AF_INET, SOCK_STREAM, 0);
        sockaddr_in serverAddr;
        memset(&serverAddr, 0, sizeof(sockaddr_in));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(_serverPort);
        inet_pton(AF_INET, _serverIp, &serverAddr.sin_addr);
        if(connect(_clientFd, (sockaddr *)&serverAddr, sizeof(sockaddr_in)) == -1)
        {
            std::cout << "CLIENT ERROR: connect failed " << errno << std::endl;
            return;
        }
        std::cout << "CLIENT INFO: connect server" << std::endl;
        char *buffWrite = new char[SENDBUFLEN];
        memset(buffWrite, 0, SENDBUFLEN);
        char msgType = MSG_LOGIN;
        memcpy(buffWrite, &msgType, sizeof(msgType));
        const char *userName = "user1";
        memcpy(buffWrite + sizeof(MSG_LOGIN), userName, sizeof(userName));
        const char *password = "12345";
        memcpy(buffWrite + sizeof(MSG_LOGIN) + USERNAMELEN, password, sizeof(password));
        write(_clientFd, buffWrite, SENDBUFLEN);
        std::cout << buffWrite <<std::endl;

        char *buffRecv = new char[RECVBUFLEN];
        read(_clientFd, buffRecv, RECVBUFLEN);
        char head;
        short int state;
        memcpy(&head, buffRecv, 1);
        memcpy(&state, buffRecv + 1, sizeof(short int));
        // std::cout << "head: " << head << " state: "<< state << std::endl;
    }
private:
    int _clientFd = -1;
    in_port_t _port = 7000;
    in_port_t _serverPort;
    const char * _serverIp = nullptr;

};

int main()
{
    Client client("10.252.1.171", SERVERPORT);
    return 0;
}