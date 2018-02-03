#ifndef ZLOTA_GODZINA_H
#define ZLOTA_GODZINA_H

#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

/**
 * @brief The Zlgodzina class
 *
 *klasa, której typami są złote godziny
 */
class Zlgodzina{
public:
    string typ;
    time_t rozp;
    time_t zakon;

    Zlgodzina(string="brak", time_t=0, time_t=0);

    /**
     * @brief CzasRozp
     * @param g nowa ZG
     *
     *nadaje zlotej godzine czas rozpoczęcia
     */
    void Rozpocznij(string typ_);
    void Zakoncz();
};
struct Lista{
    string typ_L;
    time_t rozp_L;
    time_t zakon_L;
    Lista *nast;

};
struct ListaZad{
    time_t data_zad;
    int ilosc;
    ListaZad *nast;
};
void PlikZGDoListy(string baza_danych, Lista *&glowa);
void UsunListeZG(Lista *glowa);
void ListaZGDoPliku(string baza_danych, Lista *glowa);
/**
 * @brief Zamien
 * @param czasUNIX pobieram czas w formacie time_t
 * @return funkcja zwraca czas w formie tm
 */
tm Zamien(time_t czasUNIX);

void ZadaneZGDoListy(string liczba_godzin, ListaZad *&glowa_Z );
void UsunListeZadaneZG(ListaZad *glowa);

#endif // ZLOTA_GODZINA_H
