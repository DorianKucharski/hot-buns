#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_przycisk_odbiorcy_clicked();

    void on_tabWidget_tabCloseRequested(int index);


    void on_przycisk_towary_clicked();

    void on_przycisk_sprzedaz_clicked();

    void on_przycisk_sprzedaz_przeglad_clicked();



    void on_przycisk_produkcja_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
