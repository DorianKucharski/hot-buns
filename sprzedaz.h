#ifndef SPRZEDAZ_H
#define SPRZEDAZ_H

#include <QWidget>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QSqlTableModel>
#include <QStandardItemModel>

namespace Ui {
class sprzedaz;
}

class sprzedaz : public QWidget
{
    Q_OBJECT

public:
    explicit sprzedaz(QWidget *parent = nullptr);
    ~sprzedaz();


public slots:

private slots:

    void wczytaj_odbiorcow();

    void wczytaj_towary();

    void on_przycisk_wz_clicked();

    void on_przycisk_faktura_clicked();

    void on_przycisk_paragon_clicked();

    void on_tablica_odbiorcy_doubleClicked(const QModelIndex &index);

    void zmiana(QStandardItem* item);

    void generowanie_naglowka_dokumentu();

    void liczenie_wartosci();

    void usuwanie_pustych_pozycji();

    void on_przycisk_zapisz_clicked();

    void zapisywanie();

    void on_pole_data_userDateChanged(const QDate &date);

private:
    Ui::sprzedaz *ui;
    QSqlQuery qry;
    QStandardItemModel *model_sprzedaz;
    QDate data;

    int typ_dokumentu;
    int numer_dokumentu;
    int id_odbiorcy;
    QString nazwa_dokumentu;
    QString nazwa_odbiorcy;
    double wartosc_netto_dokumentu;
    double wartosc_brutto_dokumentu;
};

#endif // SPRZEDAZ_H
