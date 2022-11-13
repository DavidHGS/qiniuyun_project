#ifndef WHITEBOARDCLIENT_H
#define WHITEBOARDCLIENT_H

#include "define.h"
#include <QObject>
#include <QTcpSocket>

class WhiteBoardClient : public QObject
{
    Q_OBJECT
public:
    explicit WhiteBoardClient(QObject *parent = nullptr);
    void connectToServer(QString serverIp, unsigned int serverPort);
    void sendData(const char *data, int len);
private:
    void init();

signals:
    void readData(const char*, int len = RECVBUFLEN);
public slots:
    void readSlot();
    
private:
    QTcpSocket *_clientFd;
    char *buffSend;
    char *buffRecv;
};

#endif // WHITEBOARDCLIENT_H
