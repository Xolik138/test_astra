#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QtNetwork/QTcpServer>

#include "worker.h"


class Server: public QObject
{
    Q_OBJECT
public:
    Server(QObject * parent);
    ~Server();
};

#endif // SERVER_H
