#include "dbworker.h"

DbWorker::DbWorker()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("FirstDB");
    db.setUserName("demo");
    db.setPassword("password");
}

bool DbWorker::initDb()
{
    return true;
}
bool DbWorker::get_info_db(std::string& host, std::string& dbName, std::string& userName, std::string& pass )
{
    return true;
}
