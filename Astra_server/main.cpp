#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);
    Server server;
    // if (argc > 1) {
    //     server.start(int(argv[1]));
    // }
    // else
    // {
        server.start();
    // }
    return a.exec();
}
