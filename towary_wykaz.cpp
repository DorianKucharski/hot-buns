#include "towary_wykaz.h"
#include "ui_towary_wykaz.h"
#include "towary_edycja.h"
#include <QDebug>


towary_wykaz::towary_wykaz(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::towary_wykaz)
{

    ui->setupUi(this);
    odswiez();

}

towary_wykaz::~towary_wykaz()
{
    delete ui;
}

void towary_wykaz::odswiez()
{
    QSqlQueryModel * model = new QSqlQueryModel;
    qry.prepare("select * from towary");
    qry.exec();
    model->setQuery(qry);
    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void towary_wykaz::on_tableView_clicked(const QModelIndex &index)
{
    id = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString();
    nazwa = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),1)).toString();
}

void towary_wykaz::on_przycisk_dodaj_clicked()
{
    towary_edycja edycja;
    edycja.setModal(true);
    edycja.exec();
}

void towary_wykaz::on_przycisk_edytuj_clicked()
{
    towary_edycja edycja;
    edycja.id = id;
    edycja.setWindowTitle(QString("Edycja: %1").arg(nazwa));
    edycja.wczytaj_dane();
    edycja.exec();

}

void towary_wykaz::on_przycisk_odswiez_clicked()
{
    odswiez();
}

void towary_wykaz::on_tableView_doubleClicked(const QModelIndex &index)
{
    id = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString();
    QString nazwa = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),1)).toString();
    towary_edycja edycja;
    edycja.setWindowTitle(QString("Edycja: %1").arg(nazwa));
    edycja.id = id;
    edycja.wczytaj_dane();
    edycja.exec();
}
