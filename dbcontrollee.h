#ifndef DBCONTROLLEE_H
#define DBCONTROLLEE_H
#include <QString>
#include <QtSql>
#include <QDebug>

class dbcontrollee
{
public:
    dbcontrollee();
    QSqlDatabase db;
    bool connect(QString login, QString password);
};

#endif // DBCONTROLLEE_H
