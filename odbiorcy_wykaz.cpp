#include "odbiorcy_wykaz.h"
#include "ui_odbiorcy_wykaz.h"
#include "odbiorcy_edycja.h"
#include <QDebug>


odbiorcy_wykaz::odbiorcy_wykaz(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::odbiorcy_wykaz)
{

    ui->setupUi(this);
    odswiez();

}

odbiorcy_wykaz::~odbiorcy_wykaz()
{
    delete ui;
}

void odbiorcy_wykaz::odswiez()
{
    QSqlQueryModel * model = new QSqlQueryModel;
    qry.prepare("select * from odbiorcy");
    qry.exec();
    model->setQuery(qry);
    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void odbiorcy_wykaz::on_tableView_clicked(const QModelIndex &index)
{
    id = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString();
    nazwa = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),1)).toString();
}

void odbiorcy_wykaz::on_przycisk_dodaj_clicked()
{
    odbiorcy_edycja edycja;
    edycja.setModal(true);
    edycja.exec();
}

void odbiorcy_wykaz::on_przycisk_edytuj_clicked()
{
    odbiorcy_edycja edycja;
    edycja.id = id;
    edycja.setWindowTitle(QString("Edycja: %1").arg(nazwa));
    edycja.wczytaj_dane();
    edycja.setModal(true);
    edycja.exec();

}

void odbiorcy_wykaz::on_przycisk_odswiez_clicked()
{
    odswiez();
}

void odbiorcy_wykaz::on_tableView_doubleClicked(const QModelIndex &index)
{
    id = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString();
    nazwa = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),1)).toString();
    odbiorcy_edycja edycja;
    edycja.setWindowTitle(QString("Edycja: %1").arg(nazwa));
    edycja.id = id;
    edycja.wczytaj_dane();
    edycja.exec();
}
