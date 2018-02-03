#ifndef STATYSTYKI_H
#define STATYSTYKI_H

#include <QDialog>
#include "zlota_godzina.h"
#include "typy.h"
#include <time.h>
#include "mainwindow.h"
#include <math.h>

namespace Ui {
class Statystyki;
}

class Statystyki : public QDialog
{
    Q_OBJECT
    
public:
    explicit Statystyki(QWidget *parent = 0);
    ~Statystyki();
    /**
     * @brief Przegladaj
     * @param baza_danych
     * @param Liczba_godzin
     * @param licznik
     *
     *Funkcja odpowiedzialna za wyświetlanie statystyk
     */
    void Przegladaj(string baza_danych, string Liczba_godzin, int licznik);

    
private slots:
    void on_pbPoprzedni_clicked();

    void on_pbNastepny_clicked();

private:
    Ui::Statystyki *ui;
};

#endif // STATYSTYKI_H
