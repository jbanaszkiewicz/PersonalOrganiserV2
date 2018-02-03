#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "typy.h"
#include "zlota_godzina.h"
#include "statystyki.h"
#include <sstream>
#include <QTimer>
#include <QSound>
#include <iomanip>
const std::string TYPY="typy.txt";
const std::string BAZA_DANYCH="baza_danych.txt";
const std::string LICZBA_GODZIN="liczba_godzin.txt";

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTimer *timer;
    bool rodzaj;
    int czas;
    time_t czas1;
    time_t czas2;
    int lw1opcja;
    int numerek=0;
    Zlgodzina g;
    /**
     * @brief WypiszListeOdKonca
     *
     *Funkcja odpowiedzialna za wypisanie ZG w oknie od końca
     *
     *todo zbudować funkcję
     */
    void WypiszListeOdKonca();
    /**
     * @brief WypiszOdKoncaRek
     * @param glowa adres głowy listy
     * @param strumien  strumien w ktorym umieszczam dane
     */

    void WypiszOdKoncaRek(Lista *glowa, stringstream *strumien);
    void ZapiszTypyDoPliku(Type *glowa);

    
private slots:
    /**
     * @brief on_pbRozpocznij_clicked
     *
     *przycisk rozpoczynający ZG, ładujący typy na listę do wyboru
     */
    void on_pbRozpocznij_clicked();
    /**
     * @brief on_lw1_doubleClicked
     * @param index
     *
     *Funkcja wybierająca typ ZG
     */
    void on_lw1_doubleClicked(const QModelIndex &index);
    /**
     * @brief on_pbStatystyki_clicked
     *
     *Funkcja przechodząca do okna statystyki
     */
    void on_pbStatystyki_clicked();
    /**
     * @brief ZwiekszIWyswietl
     *
     *Funkcja odpowiedzialna za obsługę wyświetlania czasu
     */
    void ZwiekszIWyswietl();


    /**
     * @brief on_pbZakoncz_clicked
     *
     *Funkcja kończąca ZG
     */
    void on_pbZakoncz_clicked();

    void on_pbUsun_clicked();

    void on_pbDodaj_clicked();

    void on_pbZadaj_clicked();

    void on_pbEdytujTyp_clicked();
    /**
     * @brief on_leTyp_returnPressed
     *
     *funkcja dodaje typ po kliknięciu przycisku enter
     */
    void on_leTyp_returnPressed();

    void on_pbDataRozp_clicked();

    void on_pbDataZakon_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H


