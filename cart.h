#ifndef CART_H
#define CART_H

#include <QDialog>
#include <dbcontrollee.h>
#include <Book_cart.h>
#include <QTableView>
#include <QStandardItemModel>
namespace Ui {
class Cart;
}

class Cart : public QDialog
{
    Q_OBJECT

public:
    explicit Cart(QWidget *parent = nullptr);
    ~Cart();
    QSqlDatabase *linkDb;

    std::vector<book_cart> vec_book_cart;

    void setVec(std::vector<book_cart> vec_book_cart){
        this->vec_book_cart = vec_book_cart;
    }
    int client_id;
private slots:
    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::Cart *ui;
    QSqlQueryModel   *bookDevice;
    QStandardItemModel *model_buff;
    int temp_id;
    int count;
};

#endif // CART_H
