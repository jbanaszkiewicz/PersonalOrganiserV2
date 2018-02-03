#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer=new QTimer;
    connect(this->timer,SIGNAL(timeout()),this,SLOT(ZwiekszIWyswietl()));
    WypiszListeOdKonca();
    this->setWindowTitle("Organizer pracy systemem złotych godzin");
    ui->pbZakoncz->setEnabled(false);
    ui->sbgodz->setMaximum(23);
    ui->sbmin->setMaximum(59);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}
void MainWindow::WypiszListeOdKonca(){
///uniemozliwienie wpisania czegoś do pteLista
    numerek=0;
    ui->pteLista->setReadOnly(true);
    stringstream strumien;
    Lista *glowa=NULL;

    PlikZGDoListy(BAZA_DANYCH, glowa);
    WypiszOdKoncaRek(glowa, &strumien);
    string tekst=strumien.str();
    QString tekst_qt=tekst.c_str();
    ui->pteLista->clear();
    ui->pteLista->appendPlainText(tekst_qt);
    UsunListeZG(glowa);
///wyświetlanie ZG od początku, przewinięte
    ui->pteLista->moveCursor(QTextCursor::Start);

}

void MainWindow::WypiszOdKoncaRek(Lista *glowa, stringstream *strumien){
    tm r, z;
    if(glowa!=NULL){
        WypiszOdKoncaRek(glowa->nast, strumien);

        char bufor[ 64 ];

        ++numerek;
        r=Zamien(glowa->rozp_L);
        z=Zamien(glowa->zakon_L);
        setlocale( LC_ALL, "Polish" );
        if(r.tm_wday!=3)
            strftime( bufor, sizeof( bufor ), "%a %x %H:%M" , & r );
        else
            strftime( bufor, sizeof( bufor ), "%x %H:%M" , & r );
        int min, sek;
        min=difftime(glowa->zakon_L, glowa->rozp_L)/60;
        sek=difftime(glowa->zakon_L, glowa->rozp_L)-60*min;
        QString czaswysw;
        QString qmin, qsek;
        if(min<10)
            qmin="0"+QString::number(min);
        else
            qmin=QString::number(min);
        if(sek<10)
            qsek="0"+QString::number(sek);
        else
            qsek=QString::number(sek);

        czaswysw=qmin+":"+qsek;
        string czaswyswstr=czaswysw.toStdString();

///Przy środzie wyskakiwał błąd
        if(r.tm_wday!=3)
             *strumien << setw(4)<< left<<numerek <<setw(22)<< left<<bufor<<setw(7)<<left<<glowa->typ_L<< czaswyswstr<<endl;
        else
             *strumien << setw(4)<< left<<numerek <<"Śr "<< setw(19)<<left<<bufor<<setw(7)<<left<<glowa->typ_L<<czaswyswstr<<endl;
    }
}

void MainWindow::on_pbRozpocznij_clicked()
{

///zmienna potrzebna do numerowania wyświetlanych ZG, trzeba wyzerować, zeby po ponownym załadowaniu znów wyświetlało od 1
    numerek=0;
///zmienna potrzebna do puszczania dzwięku w różnym czasie, w zależności czy jest ZG czy przerwa
    rodzaj=1;
    lw1opcja=1;
    Type *glowa_t=NULL;
    Type *tmp=NULL;
    WczytajDoListyTypy(TYPY, glowa_t);
    tmp=glowa_t;
    ui->lw1->clear();
    while(tmp!=NULL){
        ui->lw1->addItem(tmp->n.c_str());
        tmp=tmp->nast;
    }
    //while wypisujący: ui->lw->additem(wsk->typ).c_str())
    void UsunListeTypy(Type glowa_t);
    delete glowa_t;delete tmp;
    ui->statusBar->showMessage("Wybierz typ.");
    ui->lw1->setEnabled(true);
    ui->pbStatystyki->setEnabled(false);

}

void MainWindow::on_lw1_doubleClicked(const QModelIndex &index)
{
    if(lw1opcja==1){
    time(&czas1);
    localtime(&czas1);
    string typ = ui->lw1->currentItem()->text().toStdString();
    //odniesienie do lw->aktualnie zaznaczony->jego zawartość skonwertowana z QString na string
    g.Rozpocznij(typ);
    ui->statusBar->showMessage("Zakończ");
    //QString::number(arg typu int) = konwersja int na QString
    ui->pbRozpocznij->setEnabled(false);
    ui->pbZakoncz->setEnabled(true);
    //Odliczaj();
    //1000-po jakim czasie
    timer->start(1000);
    ui->lw1->setEnabled(false);
    ui->pbStatystyki->setEnabled(true);

    }

    else if(lw1opcja==2){
        Type *glowa_t=NULL;
        Type *aktual=glowa_t;
        WczytajDoListyTypy(TYPY, glowa_t);
        if(ui->lw1->currentRow()==0){
            Type *tmp=glowa_t;
            tmp=glowa_t;
            glowa_t=glowa_t->nast;
            delete tmp;
        }
        else{
            Type *tmp=NULL;
            aktual=glowa_t;
            int licz=0;
            while(licz!=ui->lw1->currentRow()-1){
                aktual=aktual->nast;
                ++licz;
            }
            tmp=aktual->nast;
            aktual->nast=aktual->nast->nast;
            delete tmp;
            aktual=aktual->nast;
            while (aktual!=NULL) {
                aktual->nr=aktual->nr-1;
                aktual=aktual->nast;
            }
        }
        ofstream g;
        g.open(TYPY.c_str());
        aktual=glowa_t;
        while (aktual!=NULL) {
            g<<aktual->n<<endl;
            aktual=aktual->nast;
        }
        g.close();
        ui->lw1->clear();
        aktual=glowa_t;
        while(aktual!=NULL){
            ui->lw1->addItem(aktual->n.c_str());
            aktual=aktual->nast;
        }

        UsunListeTypy(glowa_t);
        delete glowa_t; delete aktual;
    }
    else{
        numerek=0;
        string typ = ui->lw1->currentItem()->text().toStdString();
        Lista *glowa=NULL;
        PlikZGDoListy(BAZA_DANYCH, glowa);
        Lista *aktual=glowa;
        while(aktual->nast!=NULL)
            aktual=aktual->nast;
        aktual->typ_L=typ;
        ListaZGDoPliku(BAZA_DANYCH, glowa);

        WypiszListeOdKonca();
        UsunListeZG(glowa);
        delete glowa;delete aktual;



    }




}

void MainWindow::ZwiekszIWyswietl(){
    time(&czas2);
    localtime(&czas2);
    czas=czas2-czas1;
    int min=czas/60;

    int sek=czas%60;
    QString czaswysw;
    QString qmin, qsek;
    if(min<10)
        qmin="0"+QString::number(min);
    else
        qmin=QString::number(min);
    if(sek<10)
        qsek="0"+QString::number(sek);
    else
        qsek=QString::number(sek);

    czaswysw=qmin+":"+qsek;
    ui->tbWyswietlacz->setText(czaswysw);
    if(rodzaj){
        if(czas==3000)
        QSound::play("plikdz.wav");
    }
    else{
        if(czas==600 || czas==900 || czas==1200 || czas==1800)
        QSound::play("plikdz.wav");
    }
}

void MainWindow::on_pbStatystyki_clicked()
{
    Statystyki dlg(this);
        //if(dlg.exec() == 1);
    dlg.exec();
}

void MainWindow::on_pbZakoncz_clicked()
{
    ui->statusBar->showMessage("Pracuj dalej :D");
    rodzaj=0;
    timer->stop();
    ui->tbWyswietlacz->clear();
    time(&czas1);
    localtime(&czas1);
    timer->start(1000);

    //dopisanie godziny zakonczenia i zapisanie zg do pliku
    g.Zakoncz();
    ofstream k;
    k.open(BAZA_DANYCH.c_str(), ios::app);

    k<<g.rozp<< " "<< g.zakon<< " "<<g.typ<<endl;

    k.close();
    ui->pbRozpocznij->setEnabled(true);
    ui->pbZakoncz->setEnabled(false);
    WypiszListeOdKonca();

}

void MainWindow::on_pbUsun_clicked()
{
    lw1opcja=2;
    Type *glowa_t=NULL;
    Type *tmp=NULL;
    WczytajDoListyTypy(TYPY, glowa_t);
    tmp=glowa_t;
    ui->lw1->clear();
    while(tmp!=NULL){
        ui->lw1->addItem(tmp->n.c_str());
        tmp=tmp->nast;
    }
    //while wypisujący: ui->lw->additem(wsk->typ).c_str())
    void UsunListeTypy(Type glowa_t);
    ui->statusBar->showMessage("Wybierz typ.");
    ui->lw1->setEnabled(true);
    delete glowa_t;delete tmp;
}

void MainWindow::on_pbDodaj_clicked()
{
    Type *glowa_t=NULL;
    Type*aktual=NULL;

    WczytajDoListyTypy(TYPY, glowa_t);
    aktual=glowa_t;
    string nowe=ui->leTyp->text().toStdString();
    if(nowe==""){
        ui->statusBar->showMessage("Nie wpisano żadnego typu");
        return;
    }
    while (aktual!=NULL) {
        if(aktual->n==nowe){
            ui->statusBar->showMessage("Taki typ już istnieje");
            return;
        }
        aktual=aktual->nast;

    }
    aktual=glowa_t;

    while(aktual->nast!=NULL){
        aktual=aktual->nast;
    }
    aktual->nast=new Type;
    aktual=aktual->nast;
    aktual->nast=NULL;
    aktual->n=nowe;
    aktual->nr=1;
    ZapiszTypyDoPliku(glowa_t);
    ui->lw1->clear();
    aktual=glowa_t;
    while(aktual!=NULL){
        ui->lw1->addItem(aktual->n.c_str());
        aktual=aktual->nast;
    }

    UsunListeTypy(glowa_t);
    ui->lw1->setEnabled(false);

    delete glowa_t;delete aktual;
    ui->leTyp->clear();





}
void  MainWindow::ZapiszTypyDoPliku(Type *glowa_t){
    ofstream g;
    g.open(TYPY.c_str());
    while (glowa_t!=NULL) {
        g<<glowa_t->n<<endl;
        glowa_t=glowa_t->nast;
    }
    g.close();
}

void MainWindow::on_pbZadaj_clicked()
{
    time_t czas;
    time(&czas);
///Otwieram plik z zadaną liczną złotych godzin
    ifstream f;
    f.open(LICZBA_GODZIN.c_str());
    tm tb;
    tb=Zamien(czas);
    int x;
    int y;
    if(f.good()){
        while (!f.eof()) {
            f>>x>>y;
        }

    }
    tm t;
    t=Zamien(x);
///sprawdzenie, czy tego dnia już nie wczytywano zadanej liczby ZG.
    if(!(tb.tm_year==t.tm_year && tb.tm_mday==t.tm_mday && tb.tm_mon==t.tm_mon)){
        int liczba=ui->sbZadaj->value();

///zapisanie zadanych ZG do pliku
        ofstream k;
        k.open(LICZBA_GODZIN.c_str(), ios::app);

        k<<endl<<czas<<" "<<liczba;
        k.close();
        ui->statusBar->showMessage("Zadano liczbę złotych godzin");

    }
    else
        ui->statusBar->showMessage("Tego dnia już zadawano liczbę złotych godzin");
    f.close();

}

void MainWindow::on_pbEdytujTyp_clicked()
{
    ui->lw1->setEnabled(true);
    lw1opcja=3;
    Type *glowa_t=NULL;
    Type *tmp=NULL;
    WczytajDoListyTypy(TYPY, glowa_t);
    tmp=glowa_t;
    ui->lw1->clear();
    while(tmp!=NULL){
        ui->lw1->addItem(tmp->n.c_str());
        tmp=tmp->nast;
    }

    UsunListeTypy(glowa_t);
    delete glowa_t;

}

void MainWindow::on_leTyp_returnPressed()
{
    Type *glowa_t=NULL;
    Type*aktual=NULL;

    WczytajDoListyTypy(TYPY, glowa_t);
    aktual=glowa_t;
    string nowe=ui->leTyp->text().toStdString();
    if(nowe==""){
        ui->statusBar->showMessage("Nie wpisano żadnego typu");
        return;
    }
    while (aktual!=NULL) {
        if(aktual->n==nowe){
            ui->statusBar->showMessage("Taki typ już istnieje");
            return;
        }
        aktual=aktual->nast;

    }
    aktual=glowa_t;

    while(aktual->nast!=NULL){
        aktual=aktual->nast;
    }
    aktual->nast=new Type;
    aktual=aktual->nast;
    aktual->nast=NULL;
    aktual->n=nowe;
    aktual->nr=1;
    ZapiszTypyDoPliku(glowa_t);
    ui->lw1->clear();
    aktual=glowa_t;
    while(aktual!=NULL){
        ui->lw1->addItem(aktual->n.c_str());
        aktual=aktual->nast;
    }

    UsunListeTypy(glowa_t);
    ui->lw1->setEnabled(false);

    delete glowa_t;delete aktual;
    ui->leTyp->clear();
}

void MainWindow::on_pbDataRozp_clicked()
{
    Lista *glowa=NULL;
    Lista *aktual=NULL;
    PlikZGDoListy(BAZA_DANYCH,glowa);
    aktual=glowa;
    while(aktual->nast!=NULL)
        aktual=aktual->nast;
    tm ost;
    ost=Zamien(aktual->rozp_L);
    ost.tm_hour=ui->sbgodz->value();
    ost.tm_min=ui->sbmin->value();
    aktual->rozp_L=mktime(&ost);
    ListaZGDoPliku(BAZA_DANYCH,glowa);
    UsunListeZG(glowa);
    delete glowa; delete aktual;

    WypiszListeOdKonca();
}
void MainWindow::on_pbDataZakon_clicked()
{
    Lista *glowa=NULL;
    Lista *aktual=NULL;
    PlikZGDoListy(BAZA_DANYCH,glowa);
    aktual=glowa;
    while(aktual->nast!=NULL)
        aktual=aktual->nast;
    tm ost;
    ost=Zamien(aktual->zakon_L);
    ost.tm_hour=ui->sbgodz2->value();
    ost.tm_min=ui->sbmin2->value();
    aktual->zakon_L=mktime(&ost);
    ListaZGDoPliku(BAZA_DANYCH,glowa);
    UsunListeZG(glowa);
    delete glowa; delete aktual;

    WypiszListeOdKonca();
}


