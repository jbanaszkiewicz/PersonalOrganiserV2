//void QTableWidget::setVerticalHeaderItem(int row, QTableWidgetItem *item)
#include "statystyki.h"
#include "ui_statystyki.h"
int licznik=0;
Statystyki::Statystyki(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Statystyki)
{
    ui->setupUi(this);
///w języku polskim wyświetla polskie zniaki, które nie są odczytywane, łątwo to zmienić, ale to jest dość czasu chłonne
///bo trzeba wykonać sztuczkę ja
    ///setlocale( LC_ALL, "Polish" );
    Przegladaj(BAZA_DANYCH, LICZBA_GODZIN, 0);
    this->setWindowTitle("Statystki");




}


Statystyki::~Statystyki()
{
    delete ui;
}


void Statystyki::on_pbPoprzedni_clicked()
{


    --licznik;
   Przegladaj(BAZA_DANYCH, LICZBA_GODZIN, licznik);


}

void Statystyki::Przegladaj(string baza_danych, string Liczba_godzin, int licznik){

    setlocale( LC_ALL, "Polish" );
    int T1[31];
    int T2[31];

    for(int i=0;i<31;++i){
        T1[i]=0;
        T2[i]=0;
    }
    Lista *glowa=NULL;
    PlikZGDoListy(baza_danych,glowa);
    Lista *aktual=NULL;
    aktual=glowa;
    tm czasbtm;
    time_t czasb;
    time(&czasb);
    localtime(&czasb);
    czasbtm=Zamien(czasb);

    tm r;
    czasbtm.tm_mon=czasbtm.tm_mon+licznik;
    czasbtm.tm_mday=1;
    czasb=mktime(&czasbtm);
    czasbtm=Zamien(czasb);
    while(aktual!=NULL){
        r=Zamien(aktual->rozp_L);
        if(r.tm_year==czasbtm.tm_year && r.tm_mon==czasbtm.tm_mon){
            ++T1[r.tm_mday-1];

        }
        aktual=aktual->nast;
    }

    ListaZad *glowa_Z=NULL;
    ListaZad *aktual_Z=NULL;

    ZadaneZGDoListy(Liczba_godzin, glowa_Z);
    aktual_Z=glowa_Z;

    while(aktual_Z!=NULL){
        r=Zamien(aktual_Z->data_zad);
        if(r.tm_year==czasbtm.tm_year && r.tm_mon==czasbtm.tm_mon){
            T2[r.tm_mday-1]=aktual_Z->ilosc;
        }
        aktual_Z=aktual_Z->nast;
    }
    double wydajnosc;
    ui->tbwyswietlanie->clear();
    for(int i=0;i<31;++i){
        if(T2[i]!=0)
///przypadek, gdy były zadane i zrobione ZG
            wydajnosc=round(double(T1[i])/T2[i]*100);
        else if(T1[i]!=0)
///były zrobione ZG, ale nie zadane
            wydajnosc=100;
        else
            wydajnosc=0;
        int dtyg;
        if(czasbtm.tm_wday==0)
            dtyg=6;
        else
            dtyg=czasbtm.tm_wday-1;
        QString tekst;
        if(wydajnosc!=0)
            tekst=QString::number(T1[i])+"/"+QString::number(T2[i])+"    "+QString::number(wydajnosc)+"%";
        else
            tekst=QString::number(T1[i])+"/"+QString::number(T2[i])+"    ---";
        ui->tbwyswietlanie->setItem(0,dtyg+i,new QTableWidgetItem(tekst));
///ustawienie nagłówków w tbwyswietlanie
        ui->tbwyswietlanie->setHorizontalHeaderLabels(QString("poniedziałek;wtorek;środa;czwartek;piątek;sobota;niedziela").split(";"));

    }

    char bufor[ 64 ];
    strftime( bufor, sizeof( bufor ), "%B %Y" , &czasbtm);
    ui->lb->setText(bufor);
    UsunListeZG(glowa);
    UsunListeZadaneZG(glowa_Z);
    delete glowa; delete aktual; delete glowa_Z; delete aktual_Z;
}

void Statystyki::on_pbNastepny_clicked()
{

    ++licznik;
    Przegladaj(BAZA_DANYCH, LICZBA_GODZIN, licznik);
}
