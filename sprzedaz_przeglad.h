#ifndef SPRZEDAZ_PRZEGLAD_H
#define SPRZEDAZ_PRZEGLAD_H

#include <QWidget>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QStandardItemModel>

namespace Ui {
class sprzedaz_przeglad;
}

class sprzedaz_przeglad : public QWidget
{
    Q_OBJECT

public:
    explicit sprzedaz_przeglad(QWidget *parent = nullptr);
    ~sprzedaz_przeglad();

private slots:
    void on_tablica_lista_dokumentow_doubleClicked(const QModelIndex &index);

    void on_pole_data_userDateChanged(const QDate &date);

    void on_comboBox_activated(int index);

private:
    Ui::sprzedaz_przeglad *ui;
    QSqlQuery qry;
    QStandardItemModel *model_przeglad;
    QDate data;
    int typ_dokumentu;

    void odswiez();
    void wczytaj_wszystkie();
    void wczytaj_wz();
    void wczytaj_faktury();
    void wczytaj_paragony();
    void wczytaj_pozycje();
};

#endif // SPRZEDAZ_PRZEGLAD_H
