#include "clientwindow.h"
#include "ui_clientwindow.h"

ClientWindow::ClientWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);

     categoryDevice = new QSqlQueryModel(this);
     bookDevice = new QSqlQueryModel(this);
     feedBackDevice = new QSqlQueryModel(this);
}

ClientWindow::~ClientWindow()
{
    delete ui;
}


void ClientWindow::on_refreshButton_clicked()
{
    for(size_t i = 0; i < vec_book_cart.size(); i++){
        qDebug() << vec_book_cart[i].book_id << "count" << vec_book_cart[i].count;
    }

    categoryDevice->setQuery("SELECT * FROM CATEGORY_BOOK", *linkDb);

    for (int i = 0; i < categoryDevice->rowCount(); ++i) {
             int id = categoryDevice->record(i).value("id").toInt();
             QString name = categoryDevice->record(i).value("category").toString();
             qDebug() << id << name;
         }

    QStringList headers;
    headers.append("id");
    headers.append("Жанр");

    for(int i = 0, j = 0; i < categoryDevice->columnCount(); i++, j++){
        categoryDevice->setHeaderData(i,Qt::Horizontal,headers[j]);
    }

    ui->categotyView->setModel(categoryDevice);
    // Устанавливаем модель на TableView
    ui->categotyView->setColumnHidden(0, true);    // Скрываем колонку с id записей
    // Разрешаем выделение строк
    ui->categotyView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    ui->categotyView->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем размер колонок по содержимому
    ui->categotyView->resizeColumnsToContents();
    ui->categotyView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->categotyView->horizontalHeader()->setStretchLastSection(true);

}

void ClientWindow::on_categotyView_clicked(const QModelIndex &index)
{
    int temp_id;
    temp_id = ui->categotyView->model()->data(ui->categotyView->model()->index(index.row(), 0)).toInt();
    QString tsql = "SELECT book_id, BOOK.named, AUTHOR.named, price, COVER.type, category FROM BOOK INNER JOIN AUTHOR_GROUP ON author_group_id = AUTHOR_GROUP.id INNER JOIN AUTHOR ON author_id1 = AUTHOR.author_id INNER JOIN COVER ON BOOK.type_id = COVER.id INNER JOIN CATEGORY_BOOK ON BOOK.category_id = CATEGORY_BOOK.id ";
    QString category = "WHERE BOOK.category_id = " + QString::number(temp_id);
    bookDevice->setQuery(tsql + category, *linkDb);

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
    ui->categotyView->horizontalHeader()->setStretchLastSection(true);
}

void ClientWindow::on_bookView_clicked(const QModelIndex &index)
{
    book_id = ui->bookView->model()->data(ui->bookView->model()->index(index.row(), 0)).toInt();

    QString tsql = "SELECT description FROM BOOK WHERE BOOK.book_id = ";
    QSqlQuery query(*linkDb);

    query.prepare(tsql + QString::number(book_id));
    query.exec();
    query.next();
    ui->textBrowser->setText(query.value("description").toString());

    query.prepare("SELECT BOOK.price FROM BOOK WHERE BOOK.book_id = " + QString::number(book_id));
    query.exec();
    query.next();
    ui->priceLabel->setText(query.value("price").toString() + " Р.");

    query.prepare("SELECT star FROM FEEDBACK WHERE book_id = " + QString::number(book_id));
    query.exec();
    double star = 0.0;
    double size = 0.0;
    while(query.next()){
        star = star + query.value("star").toDouble();
        size++;
    }
    star = star / size;
    ui->starLabel->setText("Raiting: " + QString::number(star));

    QString feedBacksql = "SELECT book_id, FIO, comment, star, date FROM FEEDBACK INNER JOIN CLIENT ON FEEDBACK.client_id = CLIENT.client_id WHERE book_id = ";
    feedBackDevice->setQuery(feedBacksql + QString::number(book_id), *linkDb);

    QStringList headers;
    headers.append("id");
    headers.append("FIO");
    headers.append("comment");
    headers.append("Star");
    headers.append("Date");

    for(int i = 0, j = 0; i < feedBackDevice->columnCount(); i++, j++){
        feedBackDevice->setHeaderData(i,Qt::Horizontal,headers[j]);
    }

    ui->feebBackView->setModel(feedBackDevice);
    // Устанавливаем модель на TableView
    ui->feebBackView->setColumnHidden(0, true);    // Скрываем колонку с id записей
    // Разрешаем выделение строк
    ui->feebBackView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    ui->feebBackView->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем размер колонок по содержимому
    ui->feebBackView->resizeColumnsToContents();
    ui->feebBackView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->feebBackView->horizontalHeader()->setStretchLastSection(true);


     tsql = "SELECT byte FROM PICTURE WHERE id = " ;
     query.prepare(tsql + QString::number(book_id));
     query.exec();
     query.next();
     ui->imageLabel->setScaledContents(true);
     QPixmap outPixmap = QPixmap();
     outPixmap.loadFromData(query.value("byte").toByteArray());
     ui->imageLabel->setPixmap(outPixmap.scaled(331,381));
}


void ClientWindow::on_pushButton_clicked()
{
    for(size_t i = 0; i < vec_book_cart.size(); i++){
        if(vec_book_cart[i].book_id == book_id){
            vec_book_cart[i].count++;
            return;
        }
    }
    book_cart book; book.book_id = book_id; book.count = 1;
    vec_book_cart.push_back(book);
}

void ClientWindow::on_pushButton_2_clicked()
{
    Cart Cart;
    Cart.setModal(true);
    Cart.linkDb = linkDb;
    Cart.setVec(vec_book_cart);
    Cart.client_id = client_id;
    Cart.exec();
}
