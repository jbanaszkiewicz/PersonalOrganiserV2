#include <iostream>
#include <time.h>
#include <fstream>
#include "typy.h"
using namespace std;

void WczytajDoListyTypy(string typy, Type *&glowa_t){
    ifstream f;
    string x;
    int licznik=1;
    Type *aktual=NULL;
///otwieram plik z typami
    f.open(typy.c_str());
    if(f.good()){
        while (!f.eof()) {
            getline(f, x);
            if(x!=""){
                if(glowa_t==NULL){
                  glowa_t=new Type;
                  aktual=glowa_t;
                }
                else{
                    aktual->nast=new Type;
                    aktual=aktual->nast;
                }
                aktual->n=x;
                aktual->nr=licznik;
                aktual->nast=NULL;

                ++licznik;
            }
        }
    }
    --licznik;
    f.close();
}
void UsunListeTypy(Type *glowa){
    while (glowa!=NULL) {
       Type *poprzednik;
       poprzednik=glowa;
       glowa=glowa->nast;
       delete poprzednik;
    }
}
