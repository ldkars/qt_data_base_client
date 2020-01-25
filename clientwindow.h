#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QDialog>
#include <dbcontrollee.h>
#include <cart.h>
#include <Book_cart.h>

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
    int client_id = 2;
    int book_id;

    std::vector<book_cart> vec_book_cart;


private slots:
    void on_refreshButton_clicked();

    void on_categotyView_clicked(const QModelIndex &index);

    void on_bookView_clicked(const QModelIndex &index);

    void on_pushButton_clicked();
    
    void on_pushButton_2_clicked();

private:
    Ui::ClientWindow *ui;
    QSqlQueryModel   *categoryDevice;
    QSqlQueryModel   *bookDevice;
    QSqlQueryModel   *feedBackDevice;
};

#endif // CLIENTWINDOW_H
