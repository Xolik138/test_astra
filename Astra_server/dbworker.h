#ifndef DBWORKER_H
#define DBWORKER_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QSettings>
#include <QSqlQuery>
#include <QDebug>

class DbWorker: public QObject
{
    Q_OBJECT
public:
    DbWorker();
    ~DbWorker();

    bool proc_req(QString, QSqlQuery&);

private:
    bool initDb();
    bool get_info_db(QString&, QString&, QString&, QString&, QString&);

    QSettings *db_info;
    QSqlDatabase db;

};

#endif // DBWORKER_H
