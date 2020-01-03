#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H
#include <QString>
#include <QtSql>


class DataBaseController
{
public:
    DataBaseController();
    QSqlDatabase db;
    bool connect(QString login, QString password);
};

#endif // DATABASECONTROLLER_H
