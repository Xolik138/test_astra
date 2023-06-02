#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    nextBlockSize = 0;
    count = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    socket->connectToHost(ui->lineEdit->text(), ui->lineEdit_2->text().toInt());

}

void MainWindow::sendToServer(QString str)
{
    Data.clear();
    QDataStream out (&Data, QIODevice::WriteOnly);
    out << quint16(0)<< str;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
    socket->write(Data);
}

void MainWindow::slotReadyRead()
{
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
            nextBlockSize = 0;
            ui->textBrowser->append(QString::number(count) + ") " + str);
        }
    }
    else
    {
        ui->textBrowser->append(QString::number(count) + ") " + "Read Error!");
    }
    ++count;
}

void MainWindow::on_pushButton_2_clicked()
{
    sendToServer(ui->lineEdit_3->text());
}


void MainWindow::on_lineEdit_3_returnPressed()
{
    sendToServer(ui->lineEdit_3->text());
}

