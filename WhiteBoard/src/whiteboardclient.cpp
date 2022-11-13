#include "whiteboardclient.h"
#include <memory>
#include <QDebug>
#include <QHostAddress>

WhiteBoardClient::WhiteBoardClient(QObject *parent) : QObject(parent)
{
    init();
}

void WhiteBoardClient::init()
{
    _clientFd = new QTcpSocket();
    buffRecv = new char[RECVBUFLEN];
    buffSend = new char[SENDBUFLEN];
    memset(buffSend, 0, RECVBUFLEN);
    memset(buffRecv, 0, SENDBUFLEN);
}

void WhiteBoardClient::connectToServer(QString serverIp, unsigned int serverPort)
{
    if(serverIp.isEmpty())
    {
        return;
    }
    _clientFd->connectToHost(QHostAddress(serverIp), serverPort);
    connect(_clientFd, SIGNAL(readyRead()), this, SLOT(readSlot()));
    qDebug() << "WhiteBoardClient::connectToServer " << _clientFd->state();
    if(_clientFd->state() == QAbstractSocket::ConnectingState)
    {
        const char *msg = "no-header\r\n\r\n{\r\n\"MachineType\":\"WINDOWS\"\r\n}\r\n";
        _clientFd->write(msg, strlen(msg));
    }
}

void WhiteBoardClient::readSlot()
{
    memset(buffRecv, 0, SENDBUFLEN);
    while(_clientFd->read(buffRecv, RECVBUFLEN) > 0)
    {
        emit readData(buffRecv);
    }
}

void WhiteBoardClient::sendData(const char *data, int len)
{
    memset(buffSend, 0, RECVBUFLEN);
    memcpy(buffSend, data, len);
    _clientFd->write(buffSend, SENDBUFLEN);
}
