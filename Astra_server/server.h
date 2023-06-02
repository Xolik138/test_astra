#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

#include "blocks.h"


class Server: public QTcpServer
{
    Q_OBJECT
public:
    Server();
    ~Server();

    QTcpSocket *socket;
    void start(int port = 1234);
private:
    QVector <QTcpSocket*> sockets;
    QByteArray Data;
    void sendToClient(QString);
    Blocks *blocks;
    quint16 nextBlockSize;
private slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();

};

#endif // SERVER_H
