#ifndef DBWORKER_H
#define DBWORKER_H

#include <QObject>
#include <QtSql/QSqlDatabase>

class DbWorker
{
    Q_OBJECT
public:
    DbWorker();

private:
    bool initDb();
    bool get_info_db(std::string&, std::string&, std::string&, std::string& );
};

#endif // DBWORKER_H
