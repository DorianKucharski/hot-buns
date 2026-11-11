#include "sprzedaz_przeglad.h"
#include "ui_sprzedaz_przeglad.h"
#include <QtDebug>


sprzedaz_przeglad::sprzedaz_przeglad(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sprzedaz_przeglad)
{
    ui->setupUi(this);
    ui->tablica_lista_dokumentow->setSelectionBehavior(QAbstractItemView::SelectRows);
    typ_dokumentu = 1;
    data = QDate::currentDate();
    ui->pole_data->setDate(data);

}

sprzedaz_przeglad::~sprzedaz_przeglad()
{
    delete ui;
}

void sprzedaz_przeglad::odswiez()
{
    if (typ_dokumentu == 0) wczytaj_wszystkie();
    if (typ_dokumentu == 1) wczytaj_wz();
    if (typ_dokumentu == 2) wczytaj_faktury();
    if (typ_dokumentu == 3) wczytaj_paragony();
}

void sprzedaz_przeglad::wczytaj_wszystkie()
{

    QSqlQueryModel * model_sql = new QSqlQueryModel;
    qry.prepare("select * from wz where data=:data");
    qry.bindValue(":data", data);
    qry.exec();
    model_sql->setQuery(qry);

    model_przeglad = new QStandardItemModel(model_sql->rowCount(),model_sql->columnCount(),this);
    for (int row = 0; row < model_sql->rowCount(); ++row)
    {
        for (int col = 0; col < model_sql->columnCount(); ++col)
        {
            QModelIndex index = model_przeglad->index(row,col,QModelIndex());
            model_przeglad->setData(index,model_sql->data(index));
        }
    }


    for (int row = 0; row < model_przeglad->rowCount(); ++row)
    {
            QModelIndex index = model_przeglad->index(row,2,QModelIndex());
            int id_odbiorcy = model_przeglad->data(index).toInt();
            qry.prepare("select nazwa from odbiorcy where id=:id_odbiorcy");
            qry.bindValue(":id_odbiorcy", id_odbiorcy);
            qry.exec(); qry.first();
            model_przeglad->setData(index, qry.value(0).toString());

    }

    model_przeglad->removeColumn(0);
    QStringList naglowki = {"Numer", "Odbiorca", "Data", "Wartość netto", "Wartość brutto"};
    model_przeglad->setHorizontalHeaderLabels(naglowki);
    ui->tablica_lista_dokumentow->setModel(model_przeglad);









    qry.prepare("select * from faktury where data=:data");
    qry.bindValue(":data", data);
    qry.exec();
    model_sql->setQuery(qry);


    for (int row = 0; row < model_sql->rowCount(); ++row)
    {
        for (int col = 0; col < model_sql->columnCount(); ++col)
        {
            QModelIndex index = model_przeglad->index(model_przeglad->rowCount(),col,QModelIndex());
            QModelIndex index_sql = model_przeglad->index(row,col,QModelIndex());
            model_przeglad->setData(index,model_sql->data(index_sql));
        }
    }







}
void sprzedaz_przeglad::wczytaj_wz()
{
    QSqlQueryModel * model_sql = new QSqlQueryModel;
    qry.prepare("select * from wz where data=:data");
    qry.bindValue(":data", data);
    qry.exec();
    model_sql->setQuery(qry);

    model_przeglad = new QStandardItemModel(model_sql->rowCount(),model_sql->columnCount(),this);
    for (int row = 0; row < model_sql->rowCount(); ++row)
    {
        for (int col = 0; col < model_sql->columnCount(); ++col)
        {
            QModelIndex index = model_przeglad->index(row,col,QModelIndex());
            model_przeglad->setData(index,model_sql->data(index));
        }
    }


    for (int row = 0; row < model_przeglad->rowCount(); ++row)
    {
            QModelIndex index = model_przeglad->index(row,2,QModelIndex());
            int id_odbiorcy = model_przeglad->data(index).toInt();
            qry.prepare("select nazwa from odbiorcy where id=:id_odbiorcy");
            qry.bindValue(":id_odbiorcy", id_odbiorcy);
            qry.exec(); qry.first();
            model_przeglad->setData(index, qry.value(0).toString());

    }

    model_przeglad->removeColumn(0);
    QStringList naglowki = {"Numer", "Odbiorca", "Data", "Wartość netto", "Wartość brutto"};
    model_przeglad->setHorizontalHeaderLabels(naglowki);
    ui->tablica_lista_dokumentow->setModel(model_przeglad);



}

void sprzedaz_przeglad::wczytaj_faktury()
{
    QSqlQueryModel * model_sql = new QSqlQueryModel;
    qry.prepare("select * from faktury where data=:data");
    qry.bindValue(":data", data);
    qry.exec();
    model_sql->setQuery(qry);

    model_przeglad = new QStandardItemModel(model_sql->rowCount(),model_sql->columnCount(),this);
    for (int row = 0; row < model_sql->rowCount(); ++row)
    {
        for (int col = 0; col < model_sql->columnCount(); ++col)
        {
            QModelIndex index = model_przeglad->index(row,col,QModelIndex());
            model_przeglad->setData(index,model_sql->data(index));
        }
    }

    for (int row = 0; row < model_przeglad->rowCount(); ++row)
    {
            QModelIndex index = model_przeglad->index(row,2,QModelIndex());
            int id_odbiorcy = model_przeglad->data(index).toInt();
            qry.prepare("select nazwa from odbiorcy where id=:id_odbiorcy");
            qry.bindValue(":id_odbiorcy", id_odbiorcy);
            qry.exec(); qry.first();
            model_przeglad->setData(index, qry.value(0).toString());

    }

    model_przeglad->removeColumn(0);
    QStringList naglowki = {"Numer", "Odbiorca", "Data", "Wartość netto", "Wartość brutto"};
    model_przeglad->setHorizontalHeaderLabels(naglowki);
    ui->tablica_lista_dokumentow->setModel(model_przeglad);

}

void sprzedaz_przeglad::wczytaj_paragony()
{
    QSqlQueryModel * model_sql = new QSqlQueryModel;
    qry.prepare("select * from paragony where data=:data");
    qry.bindValue(":data", data);
    qry.exec();
    model_sql->setQuery(qry);

    model_przeglad = new QStandardItemModel(model_sql->rowCount(),model_sql->columnCount(),this);
    for (int row = 0; row < model_sql->rowCount(); ++row)
    {
        for (int col = 0; col < model_sql->columnCount(); ++col)
        {
            QModelIndex index = model_przeglad->index(row,col,QModelIndex());
            model_przeglad->setData(index,model_sql->data(index));
        }
    }


    model_przeglad->removeColumn(0);
    QStringList naglowki = {"Numer", "Data", "Wartość netto", "Wartość brutto"};
    model_przeglad->setHorizontalHeaderLabels(naglowki);
    ui->tablica_lista_dokumentow->setModel(model_przeglad);
}

void sprzedaz_przeglad::wczytaj_pozycje()
{

}

void sprzedaz_przeglad::on_tablica_lista_dokumentow_doubleClicked(const QModelIndex &index)
{
    ui->stackedWidget->setCurrentIndex(1);
    QString nazwa_dokumentu =  ui->tablica_lista_dokumentow->model()->data(ui->tablica_lista_dokumentow->model()->index(index.row(),0)).toString();


    QSqlQueryModel * model = new QSqlQueryModel;
    if (nazwa_dokumentu.startsWith("FV"))  qry.prepare("select * from faktury_pozycje where numer_dokumentu=:numer_dokumentu");
    if (nazwa_dokumentu.startsWith("WZ"))  qry.prepare("select * from wz_pozycje where numer_dokumentu=:numer_dokumentu");
    if (nazwa_dokumentu.startsWith("PARAGON"))  qry.prepare("select * from paragony_pozycje where numer_dokumentu=:numer_dokumentu");
    qry.bindValue(":numer_dokumentu", nazwa_dokumentu);
    qry.exec();
    model->setQuery(qry);
    model->removeColumns(0,3);
    ui->tablica_dokument->setModel(model);
    ui->tablica_dokument->setSelectionBehavior(QAbstractItemView::SelectRows);

}

void sprzedaz_przeglad::on_pole_data_userDateChanged(const QDate &date)
{
    data = date;
    odswiez();
}

void sprzedaz_przeglad::on_comboBox_activated(int index)
{
    if (index == 0) typ_dokumentu = 1;
    if (index == 1) typ_dokumentu = 2;
    if (index == 2) typ_dokumentu = 3;

    odswiez();
}
