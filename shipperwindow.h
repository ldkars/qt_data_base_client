#ifndef SHIPPERWINDOW_H
#define SHIPPERWINDOW_H

#include <QDialog>
#include <dbcontrollee.h>
#include <QFileDialog>

namespace Ui {
class ShipperWindow;
}

class ShipperWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ShipperWindow(QWidget *parent = nullptr);
    ~ShipperWindow();
    QSqlDatabase *linkDb;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void on_addAuthorButton_clicked();

    void on_addAuthorView_doubleClicked(const QModelIndex &index);

    void on_houseView_doubleClicked(const QModelIndex &index);

    void on_categoryView_doubleClicked(const QModelIndex &index);

    void on_typeView_doubleClicked(const QModelIndex &index);

    void on_imageButton_clicked();

    void on_addBookButton_clicked();

private:
    Ui::ShipperWindow *ui;
    QSqlQueryModel   *categoryAuthor;
    QSqlQueryModel   *categoryHouse;
    QSqlQueryModel   *categoryCategory;
    QSqlQueryModel   *categoryCover;
    std::vector<int> vec_author_id;
    int author_id;
    int house_id;
    int caregory_id;
    int cover_id;
    int book_id;
    QString imageaddr;
    QByteArray inByteArray;
};

#endif // SHIPPERWINDOW_H
