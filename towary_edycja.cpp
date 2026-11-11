#include "towary_edycja.h"
#include "ui_towary_edycja.h"
#include "towary_wykaz.h"
#include <QMessageBox>

towary_edycja::towary_edycja(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::towary_edycja)
{
    ui->setupUi(this);

}

towary_edycja::~towary_edycja()
{
    delete ui;
}


void towary_edycja::on_przycisk_zapisz_clicked()
{

    if (id == nullptr) qry.prepare("insert into towary (nazwa, waga, cena_netto, stawkavat, cena_brutto) values (:nazwa, :waga, :cena_netto, :stawkavat, :cena_brutto)");
    else qry.prepare("update towary set id=:id, nazwa=:nazwa, waga=:waga, cena_netto=:cena_netto, stawkavat=:stawkavat, cena_brutto=:cena_brutto where id=:id");
    qry.bindValue(":id", id);
    qry.bindValue(":nazwa", ui->pole_nazwa->text());
    qry.bindValue(":waga", ui->pole_waga->value());
    qry.bindValue(":cena_netto", ui->pole_cena->value());
    qry.bindValue(":stawkavat", ui->pole_stawkavat->currentText().toDouble());
    qry.bindValue(":cena_brutto", ui->pole_cena_brutto->value());
    qry.exec();
    this->close();
}

void towary_edycja::wczytaj_dane()
{

    qry.prepare("select * from towary where id='"+id+"'");
    qry.exec();
    qry.first();
    ui->pole_nazwa->setText(qry.value(1).toString());
    ui->pole_waga->setValue(qry.value(2).toDouble());
    ui->pole_cena->setValue(qry.value(3).toDouble());
    if (qry.value(4).toDouble() == 5.0) ui->pole_stawkavat->setCurrentIndex(0);
    if (qry.value(4).toDouble() == 8.0) ui->pole_stawkavat->setCurrentIndex(1);
    if (qry.value(4).toDouble() == 23.0) ui->pole_stawkavat->setCurrentIndex(2);
    ui->pole_cena_brutto->setValue(qry.value(5).toDouble());

}

void towary_edycja::on_przycisk_usun_clicked()
{
    if (QMessageBox::Yes == QMessageBox(QMessageBox::Information, "Uwaga", "Czy na pewno chcesz usunąć?", QMessageBox::Yes|QMessageBox::No).exec())
    {
        qry.prepare("delete from towary where id='"+id+"'");
        qry.exec();
        this->close();
    }

}

void towary_edycja::on_przycisk_anuluj_clicked()
{
    this->close();
}

void towary_edycja::on_pole_cena_valueChanged(double arg1)
{
    ui->pole_cena_brutto->setValue(arg1 * (1 + ui->pole_stawkavat->currentText().toDouble() / 100));
}

void towary_edycja::on_pole_stawkavat_currentIndexChanged(const QString &arg1)
{
    ui->pole_cena_brutto->setValue(ui->pole_cena->value() * (1 + arg1.toDouble() / 100));
}

void towary_edycja::on_pole_cena_brutto_valueChanged(double arg1)
{
    ui->pole_cena->setValue(arg1 / (1 + ui->pole_stawkavat->currentText().toDouble() / 100));
}
