#ifndef DBWORKER_H
#define DBWORKER_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QSettings>


class DbWorker: public QObject
{
    Q_OBJECT
public:
    DbWorker();
    ~DbWorker();

    int proc_req(QString);

private:
    bool initDb();
    bool get_info_db(QString&, QString&, QString&, QString&, QString&);

    QSettings *db_info;
    QSqlDatabase db;

};

#endif // DBWORKER_H
