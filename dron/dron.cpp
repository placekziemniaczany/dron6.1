#include "dron.hh"
/*!
 * Rysuje kazdy element drona osobno
 *
 * \param kpi - wskaznik na modul do rysowania w gnuplocie
 */
void Dron::rysuj(std::shared_ptr<drawNS::Draw3DAPI> kpi){
    this->P.rysuj(kpi);
    this->S1.rysuj(kpi);
    this->S2.rysuj(kpi);
}
/*!
 * Konstruktor Drona
 * Wczytuje dane wierzcholkow za pomoca metody loadfromfile z plikow o
 * podanych nazwach
 */
Dron::Dron(){
    this->P.loadfromfile("korpus.txt");
    this->S1.loadfromfile("dronSruba1.txt");
    this->S2.loadfromfile("dronSruba2.txt");
}
/*!
 * Obraca drona
 * Obraca kazdy element drona osobno, dodaje nowy kat do pola Alpha
 * \param kat - obroca kazda bryle o dany kat
 * \param kpi - wskaznik do programu GnuPlot do rysowania
 */
void Dron::Obrot(double kat, std::shared_ptr<drawNS::Draw3DAPI> & kpi){
    this->Alpha =this->Alpha + kat;
    this->P.Obrot(kat, os_oz);
    this->S1.Obrot(kat, os_oz);
    this->S2.Obrot(kat, os_oz);
	this->rysuj(kpi);
}

/*!
 * Porusza drona
 * Porusza drona na plaszczyznie xy z uwzglednieniem pod jakim katem
 * jest obecnie ustawiony
 * \param odleglosc - dlugosc na jaka ma sie przeniesc dron
 * \param kat - kat wznoszenia/opadania drona
 * \param kpi - wskaznik do narysowania przemieszczenia drona
 */
void Dron::Plyn(double odleglosc, double kat,std::shared_ptr<drawNS::Draw3DAPI> & kpi){
    Wektor3D przemieszczenie;
    kat = kat*(M_PI/180);
    przemieszczenie[0]=cos(kat);
    przemieszczenie[1]=0;
    przemieszczenie[2]=sin(kat);
    this->P.PrzesunOWektor(przemieszczenie);
    this->S1.PrzesunOWektor(przemieszczenie);
    this->S2.PrzesunOWektor(przemieszczenie);
    this->rysuj(kpi);
}
/*!
 * Sprawdza kolizje drona
 *
 * Wektor pomoc to wektor odleglosci pomiedzy srodkami dronow
 * odleglosc to dlugosc tego wektora i jak odleglosc jest mniejsza
 * od sumy promieni to nastepuje kolizja
 * \param D - inteligentny wskaznik na drona
 */
bool Dron::kolizja(std::shared_ptr<Dron> D){
    double odleglosc;
    Wektor3D pomoc;
    pomoc = this->P.srodek - D->P.srodek;
    odleglosc = pomoc.dlugosc();
    if(odleglosc < this->promien + D->promien){
        return true;
    }
    else if (odleglosc == 0) {
        return false;
    }
}
/*!
 * Dodawanie nowego drona
 *
 * Funkcja korzysta z plikow srub i korpusu, laduje je funkcja loadfromfile
 * i nastepnie mozna jeszcze umiescic drona w dowolnym punkcie w zbiorniku
 */
void Dron::dodaj_przeszkode(Wektor3D pocz){
    this->P.loadfromfile("korpus.txt");
    this->S1.loadfromfile("dronSruba1.txt");
    this->S2.loadfromfile("dronSruba2.txt");
    this->P.PrzesunOWektor(pocz);
    this->S1.PrzesunOWektor(pocz);
    this->S2.PrzesunOWektor(pocz);
}
/*!
 * Zwraca ilosc wektorow
 *
 * Zwraca stworzone obiekty (wektory3D dla drona)
 */
int Dron::zwroc_punkty(){
  return this->P.zwroc_punkty()+S2.zwroc_punkty()+S1.zwroc_punkty();
  }
