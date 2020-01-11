#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QDialog>
#include <dbcontrollee.h>

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();
    QSqlDatabase *linkDb;

private slots:
    void on_refreshButton_clicked();

    void on_categotyView_clicked(const QModelIndex &index);

    void on_bookView_clicked(const QModelIndex &index);

private:
    Ui::ClientWindow *ui;
    QSqlQueryModel   *categoryDevice;
    QSqlQueryModel   *bookDevice;
};

#endif // CLIENTWINDOW_H
