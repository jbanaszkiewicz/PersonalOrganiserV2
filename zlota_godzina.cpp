#include <iostream>
#include <time.h>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include"zlota_godzina.h"
using namespace std;
Zlgodzina::Zlgodzina(string t, time_t r, time_t z){
    typ=t;
    rozp=r;
    zakon=z;
}
void PlikZGDoListy(string baza_danych, Lista *&glowa){


    string typ;
    time_t rozp;
    time_t zakon;


    Lista *aktual=NULL;
    ifstream f;
    f.open(baza_danych.c_str());
    if(f.good()){
        f>>rozp;
        f>>zakon;
        f>>typ;
        while (!f.eof()) {
            if(glowa==NULL){
              glowa=new Lista;
              aktual=glowa;
            }
            else{
                aktual->nast=new Lista;
                aktual=aktual->nast;
            }
            aktual->rozp_L=rozp;
            aktual->zakon_L=zakon;
            aktual->typ_L=typ;
            aktual->nast=NULL;
            f>>rozp;
            f>>zakon;
            f>>typ;

        }
    }


    f.close();

}
void UsunListeZG(Lista *glowa){
    while (glowa!=NULL) {
       Lista *poprzednik;
       poprzednik=glowa;
       glowa=glowa->nast;
       delete poprzednik;
    }
}

void Zlgodzina::Rozpocznij(string typ_){
    typ = typ_;
    time(&rozp);
    localtime(&rozp);   
}
void Zlgodzina::Zakoncz(){
    time(&zakon);
    localtime(&zakon);
}
tm Zamien(time_t czasUNIX){

    tm * t;
    t=new tm;
    t=localtime( & czasUNIX );
    return *t;
}

void ZadaneZGDoListy(string liczba_godzin, ListaZad *&glowa_Z ){
    ListaZad *aktual=NULL;

    time_t data;
    ifstream f;
    int ile;
    f.open(liczba_godzin.c_str());
    if(f.good()){

        while (!f.eof()) {
            f>>data;
            f>>ile;
            if(glowa_Z==NULL){
              glowa_Z=new ListaZad;
              aktual=glowa_Z;
            }
            else{
                aktual->nast=new ListaZad;
                aktual=aktual->nast;
            }

            aktual->data_zad=data;
            aktual->ilosc=ile;
            aktual->nast=NULL;
        }
    }
    f.close();
}
void UsunListeZadaneZG(ListaZad *glowa){
    while (glowa!=NULL) {
       ListaZad *poprzednik;
       poprzednik=glowa;
       glowa=glowa->nast;
       delete poprzednik;
    }
}
void ListaZGDoPliku(string baza_danych, Lista *glowa){
    ofstream g;
    g.open(baza_danych.c_str());
    while(glowa!=NULL){
        g<<glowa->rozp_L<<" ";
        g<<glowa->zakon_L<<" ";
        g<<glowa->typ_L<<endl;
        glowa=glowa->nast;
    }
    g.close();
}
