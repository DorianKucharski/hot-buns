#include "odbiorcy_edycja.h"
#include "ui_odbiorcy_edycja.h"
#include "odbiorcy_wykaz.h"
#include <QMessageBox>

odbiorcy_edycja::odbiorcy_edycja(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::odbiorcy_edycja)
{
    ui->setupUi(this);

}

odbiorcy_edycja::~odbiorcy_edycja()
{
    delete ui;
}


void odbiorcy_edycja::on_zapisz_clicked()
{

    QString nazwa, adres;
    nazwa = ui->pole_nazwa->text();
    adres = ui->pole_adres->text();
    if (id == nullptr) qry.prepare("insert into odbiorcy (nazwa, adres) values ('"+nazwa+"','"+adres+"')");
    else qry.prepare("update odbiorcy set id='"+id+"', nazwa='"+nazwa+"', adres='"+adres+"' where id='"+id+"'");
    qry.exec();
    this->close();


}

void odbiorcy_edycja::wczytaj_dane()
{

    qry.prepare("select * from odbiorcy where id='"+id+"'");
    qry.exec();
    qry.first();
    ui->pole_nazwa->setText(qry.value(1).toString());
    ui->pole_adres->setText(qry.value(2).toString());

}

void odbiorcy_edycja::on_usun_clicked()
{
    if (QMessageBox::Yes == QMessageBox(QMessageBox::Information, "Uwaga", "Czy na pewno chcesz usunąć?", QMessageBox::Yes|QMessageBox::No).exec())
    {
        qry.prepare("delete from odbiorcy where id='"+id+"'");
        qry.exec();
        this->close();
    }

}

void odbiorcy_edycja::on_pushButton_clicked()
{
    this->close();
}
