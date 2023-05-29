#include "server.h"

#include <QThread>

Server::Server(QObject * parent):
    QTcpServer(parent)
{

}

Server::~Server()
{

}
