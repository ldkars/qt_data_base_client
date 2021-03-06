#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dbcontrollee.h>
#include <clientwindow.h>
#include <shipperwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_button_connect_clicked();

private:
    Ui::MainWindow *ui;
    bool checkLineEmpty();
};
#endif // MAINWINDOW_H
