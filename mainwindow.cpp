#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <dbcontrollee.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if(!checkLineEmpty()){
        ui->statusbar->showMessage("Login or password empty. Please write", 3000);
        return;
    }

    QString login = ui->lineLoginEdit->text();
    QString password = ui->linePassEdit->text();

    dbcontrollee dbContoller;
    if(dbContoller.connect(login, password)){
       ui->statusbar->showMessage("Connected", 3000);
       ui->pushButton->setEnabled(false);
    }else{
       ui->statusbar->showMessage("Error connected", 3000);
       return;
    }

    QSqlQuery query(dbContoller.db);

    query.prepare("sp_helpuser '"+login+"'");
    query.exec();

    query.next();
    QString country = query.value("RoleName").toString();
    query.finish();

    if(country == "Client"){
        ClientWindow window;
        window.setModal(true);
        window.linkDb = &dbContoller.db;
        window.exec();
        ui->statusbar->showMessage("Welcome dear client", 30000);
    }

    if(country == "Shipper"){
        ShipperWindow window;
        window.setModal(true);
        window.linkDb = &dbContoller.db;
        window.exec();
        ui->statusbar->showMessage("Welcome dear shipper", 30000);
    }

    ui->statusbar->showMessage("You are not registered", 3000);

}

bool MainWindow::checkLineEmpty(){

    if(ui->lineLoginEdit->text() == ""){
        return false;
    }else if(ui->linePassEdit->text() == ""){
        return false;
    }

    return true;
}
