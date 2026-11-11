#include "sprzedaz.h"
#include "ui_sprzedaz.h"
#include <QDebug>
#include <QAbstractListModel>
#include <QAbstractProxyModel>
#include <QAbstractTableModel>
#include <QStandardItemModel>

sprzedaz::sprzedaz(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sprzedaz)
{
    ui->setupUi(this);
    data = QDate::currentDate();
    ui->pole_data->setDate(data);
    ui->stackedWidget->setCurrentIndex(0);
    wczytaj_odbiorcow();
}

sprzedaz::~sprzedaz()
{
    delete ui;
}

void sprzedaz::wczytaj_odbiorcow()
{
    QSqlQueryModel * model = new QSqlQueryModel;
    qry.prepare("select * from odbiorcy");
    qry.exec();
    model->setQuery(qry);
    ui->tablica_odbiorcy->setModel(model);
    ui->tablica_odbiorcy->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void sprzedaz::wczytaj_towary()
{
    QSqlQueryModel *model_towary = new QSqlQueryModel;
    qry.prepare("select * from towary");
    qry.exec();
    model_towary->setQuery(qry);
    QStandardItemModel *model_sprzedaz = new QStandardItemModel(model_towary->rowCount(),model_towary->columnCount(),this);
    for (int row = 0; row < model_towary->rowCount(); ++row)
    {
        for (int col = 0; col < model_towary->columnCount(); ++col)
        {
            QModelIndex index = model_sprzedaz->index(row,col,QModelIndex());
            model_sprzedaz->setData(index,model_towary->data(index));
        }
    }
    model_sprzedaz->removeColumn(2);
    model_sprzedaz->insertColumn(2);
    QStringList naglowki = {"Indeks", "Nazwa", "Ilosc", "Cena netto", "Stawka VAT", "Cena brutto",  "Wartosc netto", "Wartosc brutto"};
    model_sprzedaz->setHorizontalHeaderLabels(naglowki);
    ui->tablica_towary->setModel(model_sprzedaz);
    connect(model_sprzedaz, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(zmiana(QStandardItem*)));
    liczenie_wartosci();
}

void sprzedaz::zmiana(QStandardItem* item)
{
   QModelIndex index_ilosc = ui->tablica_towary->model()->index(item->row(),2,QModelIndex());
   QModelIndex index_cena_netto = ui->tablica_towary->model()->index(item->row(),3,QModelIndex());
   QModelIndex index_stawka_vat = ui->tablica_towary->model()->index(item->row(),4,QModelIndex());
   QModelIndex index_cena_brutto = ui->tablica_towary->model()->index(item->row(),5,QModelIndex());
   QModelIndex index_wartosc_netto = ui->tablica_towary->model()->index(item->row(),6,QModelIndex());
   QModelIndex index_wartosc_brutto = ui->tablica_towary->model()->index(item->row(),7,QModelIndex());
   double ilosc = ui->tablica_towary->model()->data(index_ilosc).toDouble();
   double cena_netto = ui->tablica_towary->model()->data(index_cena_netto).toDouble();
   double wartosc_netto = ilosc * cena_netto;
   double stawka_vat = 1 + (ui->tablica_towary->model()->data(index_stawka_vat).toDouble()/100);
   double cena_brutto = qRound(cena_netto * stawka_vat * 100) / 100.0;
   double wartosc_brutto = qRound(wartosc_netto * stawka_vat * 100) / 100.0;
   ui->tablica_towary->model()->setData(index_wartosc_netto, wartosc_netto);
   ui->tablica_towary->model()->setData(index_cena_brutto, cena_brutto);
   ui->tablica_towary->model()->setData(index_wartosc_brutto, wartosc_brutto);
   liczenie_wartosci();
}

void sprzedaz::liczenie_wartosci()
{
    double suma_wartosci_netto = 0; double suma_wartosci_brutto = 0;
    QModelIndex index_wartosc_netto; QModelIndex index_wartosc_brutto;

    for (int row = 0; row < ui->tablica_towary->model()->rowCount(); ++row)
    {
            index_wartosc_netto = ui->tablica_towary->model()->index(row,6,QModelIndex());
            index_wartosc_brutto = ui->tablica_towary->model()->index(row,7,QModelIndex());
            suma_wartosci_netto += ui->tablica_towary->model()->data(index_wartosc_netto).toDouble();
            suma_wartosci_brutto += ui->tablica_towary->model()->data(index_wartosc_brutto).toDouble();
    }
    ui->napis_wartosc_netto->setText(QString("Wartość netto: %1").arg(suma_wartosci_netto));
    ui->napis_wartosc_brutto->setText(QString("Wartość brutto: %1").arg(suma_wartosci_brutto));
    wartosc_netto_dokumentu = suma_wartosci_netto;
    wartosc_brutto_dokumentu = suma_wartosci_brutto;

}

void sprzedaz::usuwanie_pustych_pozycji()
{
    QModelIndex index_ilosc;
    for (int row = ui->tablica_towary->model()->rowCount() - 1; row >= 0; --row)
    {
        index_ilosc = ui->tablica_towary->model()->index(row,2,QModelIndex());
        if (ui->tablica_towary->model()->data(index_ilosc).toDouble() == 0) ui->tablica_towary->model()->removeRow(row);
    }
}

void sprzedaz::generowanie_naglowka_dokumentu()
{
    if (typ_dokumentu == 1) qry.prepare("select wz from numery_dokumentow where id=0");
    if (typ_dokumentu == 2) qry.prepare("select faktury from numery_dokumentow where id=0");
    if (typ_dokumentu == 3) qry.prepare("select paragony from numery_dokumentow where id=0");
    qry.exec(); qry.first();
    numer_dokumentu = qry.value(0).toInt() +1;

    if (typ_dokumentu == 1) nazwa_dokumentu = QString("WZ/%1/%2").arg(numer_dokumentu).arg(data.year());
    if (typ_dokumentu == 2) nazwa_dokumentu = QString("FV/%1/%2").arg(numer_dokumentu).arg(data.year());
    if (typ_dokumentu == 3) nazwa_dokumentu = QString("PARAGON/%1/%2").arg(numer_dokumentu).arg(data.year());
    if (typ_dokumentu != 3)
    {
        qry.prepare("select nazwa from odbiorcy where id=:id");
        qry.bindValue(":id", id_odbiorcy);
        qry.exec();
        qry.first();
        nazwa_odbiorcy = qry.value(0).toString();
    }

    if (typ_dokumentu == 1) ui->napis_dokument->setText(QString("WZ - %1").arg(nazwa_dokumentu));
    if (typ_dokumentu == 2) ui->napis_dokument->setText(QString("Faktura VAT - %1").arg(nazwa_dokumentu));
    if (typ_dokumentu == 3) ui->napis_dokument->setText(QString("Paragon - %1").arg(nazwa_dokumentu));
    ui->napis_odbiorca->setText(QString("Odbiorca: %1").arg(nazwa_odbiorcy));
    if (typ_dokumentu == 3) ui->napis_odbiorca->clear();

}

void sprzedaz::zapisywanie()
{
    QModelIndex index;

    for (int row = 0; row < ui->tablica_towary->model()->rowCount(); ++row)
    {
        if (typ_dokumentu == 1) qry.prepare("insert into wz_pozycje (numer_dokumentu, indeks_towaru, nazwa_towaru, ilosc, cena_netto, stawka_vat, cena_brutto, wartosc_netto, wartosc_brutto) values (:numer_dokumentu, :indeks_towaru, :nazwa_towaru, :ilosc, :cena_netto, :stawka_vat, :cena_brutto, :wartosc_netto, :wartosc_brutto)");
        if (typ_dokumentu == 2) qry.prepare("insert into faktury_pozycje (numer_dokumentu, indeks_towaru, nazwa_towaru, ilosc, cena_netto, stawka_vat, cena_brutto, wartosc_netto, wartosc_brutto) values (:numer_dokumentu, :indeks_towaru, :nazwa_towaru, :ilosc, :cena_netto, :stawka_vat, :cena_brutto, :wartosc_netto, :wartosc_brutto)");
        if (typ_dokumentu == 3) qry.prepare("insert into paragony_pozycje (numer_dokumentu, indeks_towaru, nazwa_towaru, ilosc, cena_netto, stawka_vat, cena_brutto, wartosc_netto, wartosc_brutto) values (:numer_dokumentu, :indeks_towaru, :nazwa_towaru, :ilosc, :cena_netto, :stawka_vat, :cena_brutto, :wartosc_netto, :wartosc_brutto)");

        //numer dokumentu
        qry.bindValue(":numer_dokumentu", nazwa_dokumentu);

        // indeks towaru
        index = ui->tablica_towary->model()->index(row,0,QModelIndex());
        qry.bindValue(":indeks_towaru", ui->tablica_towary->model()->data(index).toInt());

        // nazwa towaru
        index = ui->tablica_towary->model()->index(row,1,QModelIndex());
        qry.bindValue(":nazwa_towaru", ui->tablica_towary->model()->data(index).toString());

        //ilosc
        index = ui->tablica_towary->model()->index(row,2,QModelIndex());
        qry.bindValue(":ilosc", ui->tablica_towary->model()->data(index).toDouble());

        //cena netto
        index = ui->tablica_towary->model()->index(row,3,QModelIndex());
        qry.bindValue(":cena_netto", ui->tablica_towary->model()->data(index).toDouble());

        //stawka vat
        index = ui->tablica_towary->model()->index(row,4,QModelIndex());
        qry.bindValue(":stawka_vat", ui->tablica_towary->model()->data(index).toDouble());

        //cena brutto
        index = ui->tablica_towary->model()->index(row,5,QModelIndex());
        qry.bindValue(":cena_brutto", ui->tablica_towary->model()->data(index).toDouble());

        //wartosc netto
        index = ui->tablica_towary->model()->index(row,6,QModelIndex());
        qry.bindValue(":wartosc_netto", ui->tablica_towary->model()->data(index).toDouble());

        //wartosc brutto
        index = ui->tablica_towary->model()->index(row,7,QModelIndex());
        qry.bindValue(":wartosc_brutto", ui->tablica_towary->model()->data(index).toDouble());

        qry.exec();
    }

    if (typ_dokumentu == 1) qry.prepare("insert into wz (numer_dokumentu, id_odbiorcy, data, wartosc_netto, wartosc_brutto) values (:numer_dokumentu, :id_odbiorcy, :data, :wartosc_netto, :wartosc_brutto)");
    if (typ_dokumentu == 2) qry.prepare("insert into faktury (numer_dokumentu, id_odbiorcy, data, wartosc_netto, wartosc_brutto) values (:numer_dokumentu, :id_odbiorcy, :data, :wartosc_netto, :wartosc_brutto)");
    if (typ_dokumentu == 3) qry.prepare("insert into paragony (numer_dokumentu, data, wartosc_netto, wartosc_brutto) values (:numer_dokumentu, :data, :wartosc_netto, :wartosc_brutto)");
    qry.bindValue(":numer_dokumentu", nazwa_dokumentu);
    qry.bindValue(":id_odbiorcy", id_odbiorcy);
    qry.bindValue(":data", data);
    qry.bindValue(":wartosc_netto", wartosc_netto_dokumentu);
    qry.bindValue(":wartosc_brutto", wartosc_brutto_dokumentu);
    qry.exec();

    if (typ_dokumentu == 1) qry.prepare("update numery_dokumentow set id=0, wz=:numer_dokumentu where id=0");
    if (typ_dokumentu == 2) qry.prepare("update numery_dokumentow set id=0, faktury=:numer_dokumentu where id=0");
    if (typ_dokumentu == 3) qry.prepare("update numery_dokumentow set id=0, paragony=:numer_dokumentu where id=0");
    qry.bindValue(":numer_dokumentu", numer_dokumentu);
    qry.exec();
}

void sprzedaz::on_przycisk_wz_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    typ_dokumentu = 1;
}

void sprzedaz::on_przycisk_faktura_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    typ_dokumentu = 2;
}

void sprzedaz::on_przycisk_paragon_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    typ_dokumentu = 3;
    generowanie_naglowka_dokumentu();
    wczytaj_towary();
}

void sprzedaz::on_tablica_odbiorcy_doubleClicked(const QModelIndex &index)
{
    id_odbiorcy = ui->tablica_odbiorcy->model()->data(ui->tablica_odbiorcy->model()->index(index.row(),0)).toInt();
    generowanie_naglowka_dokumentu();
    wczytaj_towary();
    ui->stackedWidget->setCurrentIndex(2);

}

void sprzedaz::on_przycisk_zapisz_clicked()
{
    usuwanie_pustych_pozycji();
    zapisywanie();
    ui->przycisk_zapisz->setDisabled(true);


}

void sprzedaz::on_pole_data_userDateChanged(const QDate &date)
{
    data = date;
}
