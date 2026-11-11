#ifndef ODBIORCY_EDYCJA_H
#define ODBIORCY_EDYCJA_H

#include <QDialog>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

namespace Ui {
class odbiorcy_edycja;
}

class odbiorcy_edycja : public QDialog
{
    Q_OBJECT

public:
    explicit odbiorcy_edycja(QWidget *parent = nullptr);
    ~odbiorcy_edycja();
    QString id;
    void wczytaj_dane();


private slots:

    void on_zapisz_clicked();


    void on_usun_clicked();

    void on_pushButton_clicked();

private:
    Ui::odbiorcy_edycja *ui;
    QSqlQuery qry;

};

#endif // ODBIORCY_EDYCJA_H
