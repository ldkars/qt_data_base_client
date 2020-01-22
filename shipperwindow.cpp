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
}
