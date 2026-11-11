#ifndef TOWARY_EDYCJA_H
#define TOWARY_EDYCJA_H

#include <QDialog>

#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

namespace Ui {
class towary_edycja;
}

class towary_edycja : public QDialog
{
    Q_OBJECT

public:
    explicit towary_edycja(QWidget *parent = nullptr);
    ~towary_edycja();
    QString id;
    void wczytaj_dane();


private slots:

    void on_przycisk_zapisz_clicked();


    void on_przycisk_usun_clicked();

    void on_przycisk_anuluj_clicked();

    void on_pole_cena_valueChanged(double arg1);

    void on_pole_cena_brutto_valueChanged(double arg1);

    void on_pole_stawkavat_currentIndexChanged(const QString &arg1);

private:
    Ui::towary_edycja *ui;
    QSqlQuery qry;

};

#endif // TOWARY_EDYCJA_H
