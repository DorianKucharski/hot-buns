#ifndef ODBIORCY_WYKAZ_H
#define ODBIORCY_WYKAZ_H

#include <QWidget>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

namespace Ui {
class odbiorcy_wykaz;
}

class odbiorcy_wykaz : public QWidget
{
    Q_OBJECT

public:
    explicit odbiorcy_wykaz(QWidget *parent = nullptr);
    ~odbiorcy_wykaz();



private slots:
    void on_przycisk_dodaj_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_przycisk_edytuj_clicked();

    void on_przycisk_odswiez_clicked();

    void odswiez();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::odbiorcy_wykaz *ui;
    QSqlQuery qry;
    QString id;
    QString nazwa;


};

#endif // ODBIORCY_WYKAZ_H
