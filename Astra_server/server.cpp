#include "server.h"

#include <QDataStream>

Server::Server()
{
    nextBlockSize = 0;
}

Server::~Server()
{
    for(QTcpSocket* c_sock: sockets)
    {
        c_sock->close();
    }
    delete blocks;
}

void Server::start(int port)
{
    if (this->listen(QHostAddress::Any, port))
    {
        qDebug() << "Start server, port: " << port;
        blocks = new Blocks;
    }
    else
    {
        qDebug() << "Error start server!";
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    sockets.push_back(socket);
    qDebug() << "Client connection: " << socketDescriptor;
}

void Server::slotReadyRead()
{
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    if (in.status() == QDataStream::Ok)
    {
        for (;;)
        {
            if (nextBlockSize == 0)
            {
                if (socket->bytesAvailable() < 2)
                {
                    break;
                }
                in >> nextBlockSize;
            }
            if (socket->bytesAvailable() < nextBlockSize)
            {
                break;
            }
            QString str;
            in >> str;
            qDebug() << "Client " << socket->socketDescriptor() << "sent hash: " << str;
            std::string hash = str.toStdString();
            int t_num_block = blocks->get_block_number(hash);
            if (t_num_block > 0)
            {
                qDebug() << "Number block: " << t_num_block;
                int t_size_block = blocks->get_block_size(hash);
                qDebug() << "Size block: " << t_size_block;
                char* data = new char[t_size_block];;
                blocks->get_block_data(t_num_block, data, t_size_block);
                sendToClient(data);
                delete [] data;
            }
            else
            {
                qDebug() << "No block with this hash!";
                sendToClient("No block with this hash!");
            }
            nextBlockSize = 0;
            break;
        }
    }
    else
    {
        qDebug() << "DataStream error";
    }
}

void Server::sendToClient(QString str)
{
    Data.clear();
    QDataStream out (&Data, QIODevice::WriteOnly);

    out << quint16(0) << str;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
    socket->write(Data);
}
