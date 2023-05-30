#include "dbworker.h"

#include <QString>
#include <QDebug>
#include <QCoreApplication>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QFile>

DbWorker::DbWorker()
{
    QString workFile = QDir::homePath()+"/test_astra.ini";
    QFile iniFile(workFile);
    bool isFile = iniFile.exists();
#if defined(linux) || defined(__linux)
    db_info = new QSettings(workFile, QSettings::IniFormat);
#endif
#if defined(_WIN32) || defined (_WIN64)
    db_info = new QSettings(workFile, QSettings::IniFormat);
#endif
    if (!isFile)
    {
        if (db_info->isWritable())
        {
            db_info->beginGroup("InfoDB");
            db_info->setValue("typeDb", "QPSQL");
            db_info->setValue("host", "127.0.0.1");
            db_info->setValue("dbName", "astra");
            db_info->setValue("user", "postgres");
            db_info->setValue("pass", "12345678");
            db_info->endGroup();
            db_info->sync();
        }
    }
    if(!initDb())
    {
        qDebug() << "Database connection error";
        qDebug() << db.lastError();
        QCoreApplication::exit();
    }
    proc_req("SELECT * FROM TEST;"); // DELETE
}

DbWorker::~DbWorker()
{
    delete db_info;
    db.close();
    qDebug() << "Close DB";
    // delete db;
}

bool DbWorker::initDb()
{
    QString typeDb;
    QString database;
    QString dbName;
    QString user;
    QString pass;

    get_info_db(typeDb, database, dbName, user, pass);
    db = QSqlDatabase::addDatabase(typeDb);
    db.setHostName(database);
    db.setDatabaseName(dbName);
    db.setUserName(user);
    db.setPassword(pass);

    bool conn = db.open();
    return conn;
}
bool DbWorker::get_info_db(QString& typeDb, QString& host, QString& dbName, QString& userName, QString& pass )
{
    db_info->beginGroup("InfoDB");
    typeDb = db_info->value("typeDb").toString();
    host = db_info->value("host").toString();
    dbName = db_info->value("dbName").toString();
    userName = db_info->value("user").toString();
    pass = db_info->value("pass").toString();
    db_info->endGroup();

    qDebug() << "TypeDB: " << typeDb;
    qDebug() << "Host: " << host;
    qDebug() << "DbName: " << dbName;
    qDebug() << "User: " << userName;
    qDebug() << "Pass: " << pass;

    return true;
}

int DbWorker::proc_req(QString req)
{
    QSqlQuery query;
    query.exec(req);

    int ans;
    while (query.next())
    {
        qDebug() << query.value(0).toInt();
        ans = query.value(0).toInt();
    }
    return ans;
}
