#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "odbiorcy_wykaz.h"
#include "odbiorcy_edycja.h"
#include "towary_wykaz.h"
#include "sprzedaz.h"
#include "sprzedaz_przeglad.h"
#include "produkcja.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Hot Buns");




    QSqlDatabase baza = QSqlDatabase::addDatabase("QSQLITE");
    baza.setDatabaseName("baza.db");

    if(!baza.open()) ui->napis_statusbazydanych->setText("Status bazy danych: Nie połączono");
    else ui->napis_statusbazydanych->setText("Status bazy danych: Połączono");


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}

void MainWindow::on_przycisk_odbiorcy_clicked()
{
    odbiorcy_wykaz* wsk_odbiorcy = new odbiorcy_wykaz();
    ui->tabWidget->addTab(wsk_odbiorcy, "Odbiorcy");
    ui->tabWidget->setCurrentWidget(wsk_odbiorcy);
}

void MainWindow::on_przycisk_towary_clicked()
{
    towary_wykaz* wsk_towary = new towary_wykaz();
    ui->tabWidget->addTab(wsk_towary, "Towary");
    ui->tabWidget->setCurrentWidget(wsk_towary);
}



void MainWindow::on_przycisk_sprzedaz_clicked()
{
    sprzedaz* wsk_sprzedaz = new sprzedaz();
    ui->tabWidget->addTab(wsk_sprzedaz, "Sprzedaz");
    ui->tabWidget->setCurrentWidget(wsk_sprzedaz);
}


void MainWindow::on_przycisk_sprzedaz_przeglad_clicked()
{
    sprzedaz_przeglad* wsk_sprzedaz_przeglad = new sprzedaz_przeglad();
    ui->tabWidget->addTab(wsk_sprzedaz_przeglad, "Przeglad Sprzedaży");
    ui->tabWidget->setCurrentWidget(wsk_sprzedaz_przeglad);
}

void MainWindow::on_przycisk_produkcja_clicked()
{
    produkcja* wsk_produkcja = new produkcja();
    ui->tabWidget->addTab(wsk_produkcja, "Produkcja");
    ui->tabWidget->setCurrentWidget(wsk_produkcja);

}
