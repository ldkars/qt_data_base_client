#include "shipperwindow.h"
#include "ui_shipperwindow.h"

ShipperWindow::ShipperWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShipperWindow)
{
    ui->setupUi(this);
    categoryAuthor = new QSqlQueryModel(this);
    categoryHouse = new QSqlQueryModel(this);
    categoryCategory = new QSqlQueryModel(this);
    categoryCover = new QSqlQueryModel(this);
}

ShipperWindow::~ShipperWindow()
{
    delete ui;
}

void ShipperWindow::on_pushButton_clicked()
{

}

void ShipperWindow::on_pushButton_2_clicked()
{

    categoryAuthor->setQuery("SELECT author_id, FIO, named, CIITY.name, date, date_dead FROM AUTHOR INNER JOIN CIITY ON city_id = CIITY.id", *linkDb);

    QStringList headers;
    headers.append("id");
    headers.append("FIO");
    headers.append("named");
    headers.append("CITY");
    headers.append("DATE");
    headers.append("DATE_DEAD");

    for(int i = 0, j = 0; i < categoryAuthor->columnCount(); i++, j++){
        categoryAuthor->setHeaderData(i,Qt::Horizontal,headers[j]);
    }

    ui->addAuthorView->setModel(categoryAuthor);
    // Устанавливаем модель на TableView
    ui->addAuthorView->setColumnHidden(0, true);    // Скрываем колонку с id записей
    // Разрешаем выделение строк
    ui->addAuthorView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    ui->addAuthorView->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем размер колонок по содержимому
    ui->addAuthorView->resizeColumnsToContents();
    ui->addAuthorView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->addAuthorView->horizontalHeader()->setStretchLastSection(true);



    categoryHouse->setQuery("SELECT id, named, country_title FROM PUBLISHING_HOUSE INNER JOIN COUNTRY on PUBLISHING_HOUSE.country_id = COUNTRY.country_id", *linkDb);

    ui->houseView->setModel(categoryHouse);
    // Устанавливаем модель на TableView
    ui->houseView->setColumnHidden(0, true);    // Скрываем колонку с id записей
    // Разрешаем выделение строк
    ui->houseView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    ui->houseView->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем размер колонок по содержимому
    ui->houseView->resizeColumnsToContents();
    ui->houseView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->houseView->horizontalHeader()->setStretchLastSection(true);


    categoryCategory->setQuery("SELECT * FROM CATEGORY_BOOK", *linkDb);

    ui->categoryView->setModel(categoryCategory);
    // Устанавливаем модель на TableView
    ui->categoryView->setColumnHidden(0, true);    // Скрываем колонку с id записей
    // Разрешаем выделение строк
    ui->categoryView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    ui->categoryView->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем размер колонок по содержимому
    ui->categoryView->resizeColumnsToContents();
    ui->categoryView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->categoryView->horizontalHeader()->setStretchLastSection(true);

    categoryCover->setQuery("SELECT * FROM COVER", *linkDb);

    ui->typeView->setModel(categoryCover);
    // Устанавливаем модель на TableView
    ui->typeView->setColumnHidden(0, true);    // Скрываем колонку с id записей
    // Разрешаем выделение строк
    ui->typeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    ui->typeView->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем размер колонок по содержимому
    ui->typeView->resizeColumnsToContents();
    ui->typeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->typeView->horizontalHeader()->setStretchLastSection(true);

}


void ShipperWindow::on_addAuthorButton_clicked()
{

}

void ShipperWindow::on_addAuthorView_doubleClicked(const QModelIndex &index)
{
    author_id = ui->addAuthorView->model()->data(ui->addAuthorView->model()->index(index.row(), 0)).toInt();

    for(size_t i = 0; i < vec_author_id.size(); i++){
        if(vec_author_id[i] == author_id){
            return;
        }
    }
    vec_author_id.push_back(author_id);

    QString tsql = "SELECT FIO, named, CIITY.name, date, date_dead FROM AUTHOR INNER JOIN CIITY ON city_id = CIITY.id WHERE author_id = ";
    QSqlQuery query(*linkDb);

    query.prepare(tsql + QString::number(author_id));
    query.exec();
    query.next();
    ui->listWidget->addItem(query.value("FIO").toString());
}

void ShipperWindow::on_houseView_doubleClicked(const QModelIndex &index)
{
    house_id = ui->houseView->model()->data(ui->houseView->model()->index(index.row(), 0)).toInt();
}

void ShipperWindow::on_categoryView_doubleClicked(const QModelIndex &index)
{
    caregory_id = ui->categoryView->model()->data(ui->categoryView->model()->index(index.row(), 0)).toInt();
}

void ShipperWindow::on_typeView_doubleClicked(const QModelIndex &index)
{
    cover_id = caregory_id = ui->typeView->model()->data(ui->typeView->model()->index(index.row(), 0)).toInt();
}

void ShipperWindow::on_imageButton_clicked()
{
    imageaddr = QFileDialog::getOpenFileName(0, "Open Image");
    qDebug() << imageaddr;
    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(imageaddr));

    QPixmap inPixmap = QPixmap(imageaddr);         // Сохраняем его в изображение объекта QPixmap                      // Создаём объект QByteArray для сохранения изображения
    QBuffer inBuffer( &inByteArray );              // Сохранение изображения производим через буффер
    inBuffer.open( QIODevice::WriteOnly );         // Открываем буффер
    inPixmap.save( &inBuffer, "PNG" );             // Записываем inPixmap в inByteArray






   /* QString tsql = "SELECT byte FROM PICTURE WHERE id = 4";
    query.prepare(tsql);
    query.exec();
    query.next();

    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData(query.value("byte").toByteArray());
    ui->label->setPixmap(outPixmap.scaled(500,300));*/
}

void ShipperWindow::on_addBookButton_clicked()
{
    QSqlQuery query(*linkDb);
    query.prepare("EXEC insertBook :named, :price, :type_id, :house_id, :category_id, :desc, :date_public, :date_print");
    query.bindValue(":named", ui->lineEditBookName->text());
    query.bindValue(":price",   ui->spinBox->value());
    query.bindValue(":type_id",  cover_id);
    query.bindValue(":house_id",  house_id);
    query.bindValue(":category_id",   caregory_id);
    query.bindValue(":desc",   ui->plainTextEdit->toPlainText());
    query.bindValue(":date_public",   ui->datePublic->text());
    query.bindValue(":date_print",   ui->datePrint->text());

    if(!query.exec()){
        qDebug() << query.lastError().text();
    }

    query.prepare("getID");
    query.exec();
    query.next();
    book_id = query.value("book_id").toInt();

    query.prepare("INSERT INTO PICTURE  VALUES(:id, :byte)");
    query.bindValue(":id", book_id);
    query.bindValue(":byte", inByteArray);

    if(!query.exec()){
        qDebug() << query.lastError().text();
    }

    switch (vec_author_id.size()) {
        case 1:
            query.prepare("EXEC insertGroupAuthor1 :book_id, :id");
            query.bindValue(":id", vec_author_id[0]);
            query.exec();
            break;
        case 2:
            query.prepare("EXEC insertGroupAuthor2 :book_id, :id, :id2");
            query.bindValue(":id1", vec_author_id[0] );
            query.bindValue(":id2", vec_author_id[1]);
            query.exec();
            break;
        case 3:
            query.prepare("EXEC insertGroupAuthor3 :book_id, :id, :id2, id3");
            query.bindValue(":id1", vec_author_id[0] );
            query.bindValue(":id2", vec_author_id[1]);
            query.bindValue(":id3", vec_author_id[2]);
            query.exec();
            break;
        case 4:
            query.prepare("EXEC insertGroupAuthor4 :book_id, :id, :id2, :id3, :id4");
            query.bindValue(":id1", vec_author_id[0] );
            query.bindValue(":id2", vec_author_id[1]);
            query.bindValue(":id3", vec_author_id[2]);
            query.bindValue(":id4", vec_author_id[3]);
            query.exec();
            break;
        case 5:
            query.prepare("EXEC insertGroupAuthor5 :book_id, :id, :id2, :id3, :id4, :id5");
            query.bindValue(":id1", vec_author_id[0] );
            query.bindValue(":id2", vec_author_id[1]);
            query.bindValue(":id3", vec_author_id[2]);
            query.bindValue(":id4", vec_author_id[3]);
            query.bindValue(":id5", vec_author_id[4]);
            query.exec();
            break;
   }
}
