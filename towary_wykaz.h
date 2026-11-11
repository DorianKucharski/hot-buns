#ifndef TOWARY_WYKAZ_H
#define TOWARY_WYKAZ_H

#include <QWidget>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

namespace Ui {
class towary_wykaz;
}

class towary_wykaz : public QWidget
{
    Q_OBJECT

public:
    explicit towary_wykaz(QWidget *parent = nullptr);
    ~towary_wykaz();



private slots:
    void on_przycisk_dodaj_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_przycisk_edytuj_clicked();

    void on_przycisk_odswiez_clicked();

    void odswiez();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::towary_wykaz *ui;
    QSqlQuery qry;
    QString id;
    QString nazwa;


};

#endif // TOWARY_WYKAZ_H
