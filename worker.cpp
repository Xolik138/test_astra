#include "worker.h"
#include "crypto.h"
#include "dbworker.h"

#include <QDebug>

Worker::Worker()
{
    qDebug() << "Worker";
    DbWorker bl;
}
