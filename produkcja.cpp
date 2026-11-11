#include "produkcja.h"
#include "ui_produkcja.h"

produkcja::produkcja(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::produkcja)
{
    ui->setupUi(this);
    data = QDate::currentDate();
    ui->pole_data->setDate(data);
    odswiez();

}

produkcja::~produkcja()
{
    delete ui;
}

void produkcja::odswiez()
{
    QSqlQueryModel *model_towary = new QSqlQueryModel;
    qry.prepare("select * from towary");
    qry.exec();
    model_towary->setQuery(qry);

    QStandardItemModel *model_produkcja = new QStandardItemModel(model_towary->rowCount(),3,this);
    for (int row = 0; row < model_towary->rowCount(); ++row)
    {
        for (int col = 0; col < 2; ++col)
        {
            QModelIndex index = model_produkcja->index(row,col,QModelIndex());
            model_produkcja->setData(index,model_towary->data(index));
        }
    }
    model_produkcja->removeColumn(2);
    model_produkcja->insertColumn(2);

    for (int row = 0; row < model_produkcja->rowCount(); ++row)
    {
        QModelIndex index_indeks_towaru = model_produkcja->index(row,0,QModelIndex());
        QModelIndex index_ilosc = model_produkcja->index(row,2,QModelIndex());
        model_produkcja->setData(index_ilosc, oblicz_ilosci(model_produkcja->data(index_indeks_towaru).toInt()));
    }

    QStringList naglowki = {"Indeks", "Nazwa", "Ilosc"};
    model_produkcja->setHorizontalHeaderLabels(naglowki);
    ui->tablica_produkcja->setModel(model_produkcja);

}

double produkcja::oblicz_ilosci(int indeks_towaru)
{

    double ilosc = 0;
    QSqlQuery qry2;
    qry.prepare("select numer_dokumentu from faktury where data=:data");
    qry.bindValue(":data", data);
    qry.exec();
    while (qry.next())

    {
        qry2.prepare("select ilosc from faktury_pozycje where indeks_towaru=:indeks_towaru AND numer_dokumentu=:numer_dokumentu");
        qry2.bindValue(":indeks_towaru", indeks_towaru);
        qry2.bindValue(":numer_dokumentu", qry.value(0).toString());
        qry2.exec();
        while (qry2.next()) ilosc += qry2.value(0).toDouble();


    }

    qry.prepare("select numer_dokumentu from wz where data=:data");
    qry.bindValue(":data", data);
    qry.exec();
    while (qry.next())

    {
        qry2.prepare("select ilosc from wz_pozycje where indeks_towaru=:indeks_towaru AND numer_dokumentu=:numer_dokumentu");
        qry2.bindValue(":indeks_towaru", indeks_towaru);
        qry2.bindValue(":numer_dokumentu", qry.value(0).toString());
        qry2.exec();
        while (qry2.next()) ilosc += qry2.value(0).toDouble();


    }

    qry.prepare("select numer_dokumentu from paragony where data=:data");
    qry.bindValue(":data", data);
    qry.exec();
    while (qry.next())

    {
        qry2.prepare("select ilosc from paragony_pozycje where indeks_towaru=:indeks_towaru AND numer_dokumentu=:numer_dokumentu");
        qry2.bindValue(":indeks_towaru", indeks_towaru);
        qry2.bindValue(":numer_dokumentu", qry.value(0).toString());
        qry2.exec();
        while (qry2.next()) ilosc += qry2.value(0).toDouble();


    }

    return ilosc;
}


void produkcja::on_pole_data_userDateChanged(const QDate &date)
{
    data = date;
    odswiez();
}
