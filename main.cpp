#include "mainwindow.h"
#include <QDebug>

#include <QApplication>

#include <QString>
#include <QtSql>

const QString connection_string_sqlauth =
        QString("DRIVER={%1};SERVER=%2;PORT=%3;DATABASE=%4;UID=%5;PWD=%6");


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
