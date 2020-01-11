#include "dbcontrollee.h"

dbcontrollee::dbcontrollee()
{

}

bool dbcontrollee::connect(QString login, QString password){
    db = QSqlDatabase();
    db.removeDatabase("example-connection"); // remove old connection if exists
    db = QSqlDatabase::addDatabase("QODBC", "example-connection");

    QString driver = "SQL Server";
    QString server = "DESKTOP-F4HC3G1\\SQLEXPRESS";
    int port = 1433;
    QString database  = "BookTrade";
    const QString connection_string_sqlauth =
            QString("DRIVER={%1};SERVER=%2;PORT=%3;DATABASE=%4;UID=%5;PWD=%6");

    qDebug() << connection_string_sqlauth.arg(driver).arg(server).arg(port).arg(database)
                .arg(login).arg(password);

    db.setDatabaseName(connection_string_sqlauth.arg(driver).arg(server).arg(port).arg(database)
                       .arg(login).arg(password));

    return db.open();
}
