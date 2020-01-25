#include "cart.h"
#include "ui_cart.h"

Cart::Cart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cart)
{
    ui->setupUi(this);
    bookDevice = new QSqlQueryModel(this);
}

Cart::~Cart()
{
    delete ui;
}

void Cart::on_pushButton_2_clicked()
{

    this->model_buff = new QStandardItemModel(vec_book_cart.size(), 4 , this);
    ui->tableView->setModel(model_buff);

    QModelIndex index_named;
        for(int i = 0; i < vec_book_cart.size(); i++){

            QSqlQuery query(*linkDb);
            int book_id = vec_book_cart[i].book_id;
            query.prepare("SELECT * FROM BOOK WHERE book_id = " + QString::number(book_id));
            query.exec();
            query.next();

            index_named = model_buff->index(i, 0);
            model_buff->setData(index_named, vec_book_cart[i].book_id);

            index_named = model_buff->index(i,1);
            model_buff->setData(index_named, query.value("named").toString());

            index_named = model_buff->index(i, 2);
            model_buff->setData(index_named, vec_book_cart[i].count);

            index_named = model_buff->index(i, 3);
            model_buff->setData(index_named, query.value("price").toInt() * vec_book_cart[i].count);
        }

    /*bookDevice->setQuery("", *linkDb);

    QStringList headers;
    headers.append("id");
    headers.append("Название");
    headers.append("Автор");
    headers.append("Цена");
    headers.append("Тип обложки");
    headers.append("Категория");

    for(int i = 0, j = 0; i < bookDevice->columnCount(); i++, j++){
        bookDevice->setHeaderData(i,Qt::Horizontal,headers[j]);
    }


    ui->bookView->setModel(bookDevice);
    // Устанавливаем модель на TableView
    ui->bookView->setColumnHidden(0, true);    // Скрываем колонку с id записей
    // Разрешаем выделение строк
    ui->bookView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    ui->bookView->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем размер колонок по содержимому
    ui->bookView->resizeColumnsToContents();
    ui->bookView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->categotyView->horizontalHeader()->setStretchLastSection(true);*/
}

void Cart::on_tableView_clicked(const QModelIndex &index)
{
    temp_id = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toInt();
    count = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 2)).toInt();
}

void Cart::on_pushButton_clicked()
{
    QSqlQuery query(*linkDb);
    query.prepare("EXEC BUE :id, :book_id, :count");
    query.bindValue(":id", client_id);
    query.bindValue(":book_id",   temp_id);
    query.bindValue(":count",  count);

    if(!query.exec()){
        qDebug() << query.lastError().text();
    }

    for(int i = 0; i < vec_book_cart.size(); i++){
        if(vec_book_cart[i].book_id == temp_id){
            vec_book_cart.erase(vec_book_cart.begin() + i);
        }
    }
}
