#ifndef PRODUKCJA_H
#define PRODUKCJA_H

#include <QWidget>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QSqlTableModel>
#include <QStandardItemModel>

namespace Ui {
class produkcja;
}

class produkcja : public QWidget
{
    Q_OBJECT

public:
    explicit produkcja(QWidget *parent = nullptr);
    ~produkcja();


private slots:
    void on_pole_data_userDateChanged(const QDate &date);

private:
    Ui::produkcja *ui;
    QSqlQuery qry;
    QStandardItemModel *model_produkcja;
    QDate data;

    void odswiez();
    double oblicz_ilosci(int indeks_towaru);
};

#endif // PRODUKCJA_H
