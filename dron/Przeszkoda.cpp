#include "Przeszkoda.hh"
#include "dron.hh"

bool Przeszkoda_prostopadloscian::kolizja(std::shared_ptr <Dron> Dronek){
    Wektor3D i, j, k, v;
for(unsigned int i = 0; i<this->Tablica_wierzcholkow.size(); i++){
       for (unsigned int j = 0; j<ROZMIAR; j++)
       if(Tablica_wierzcholkow[i][j]<0){
this->Tablica_wierzcholkow[i][j] = this->Tablica_wierzcholkow[i][j] - Dronek->promien;
}
else if (Tablica_wierzcholkow[i][j]>0){
this->Tablica_wierzcholkow[i][j] = this->Tablica_wierzcholkow[i][j] + Dronek->promien;
}
else {
this->Tablica_wierzcholkow[i][j] = this->Tablica_wierzcholkow[i][j];
}
}
i=this->Tablica_wierzcholkow[1] - this->Tablica_wierzcholkow[0];
j = this->Tablica_wierzcholkow[3] - this->Tablica_wierzcholkow[0];
k = this->Tablica_wierzcholkow[4] - this->Tablica_wierzcholkow[0];
v = Dronek->P.srodek - this->Tablica_wierzcholkow[0];
if (v*i>0 && v*i<i*i){
    if (v*j>0 && v*j<j*j){
        if (v*k>0 && v*k<k*k){
            return true;
        }
        else {return false;}
    }
    else {return false;}
}
else {return false;}
for(unsigned int i = 0; i<this->Tablica_wierzcholkow.size(); i++){
       for (unsigned int j = 0; j<ROZMIAR; j++)
       if(Tablica_wierzcholkow[i][j]<0){
this->Tablica_wierzcholkow[i][j] = this->Tablica_wierzcholkow[i][j] + Dronek->promien;
}
else if (Tablica_wierzcholkow[i][j]>0){
this->Tablica_wierzcholkow[i][j] = this->Tablica_wierzcholkow[i][j] - Dronek->promien;
}
else {
this->Tablica_wierzcholkow[i][j] = this->Tablica_wierzcholkow[i][j];
}
}
}


bool Woda::kolizja(std::shared_ptr <Dron> Dronek){
  for (unsigned int i = 0; i<Tablica_wierzcholkow.size(); i++){
    if(this->Tablica_wierzcholkow[i][2]>0){
      this->Tablica_wierzcholkow[i][2] = this->Tablica_wierzcholkow[i][2] - Dronek->promien;}
    else {
      this->Tablica_wierzcholkow[i][2] = this->Tablica_wierzcholkow[i][2] + Dronek->promien;}
    if (Dronek->P.srodek[2]==this->Tablica_wierzcholkow[i][2]){
      return true;}
    else {
      return false;}
    if(this->Tablica_wierzcholkow[i][2]>0){
      this->Tablica_wierzcholkow[i][2] = this->Tablica_wierzcholkow[i][2] + Dronek->promien;}
    else {
      this->Tablica_wierzcholkow[i][2] = this->Tablica_wierzcholkow[i][2] - Dronek->promien;}
  }
}
  

void Przeszkoda_prostopadloscian::dodaj_przeszkode(Wektor3D pocz){
  this->loadfromfile("korpus.txt");
  this->PrzesunOWektor(pocz);
}
void Woda::dodaj_przeszkode(Wektor3D pocz){}

void Przeszkoda_prostopadloscian::skaluj(double r){
  for (unsigned int i = 0; i<Tablica_wierzcholkow.size(); ++i){
    Tablica_wierzcholkow[i]=Tablica_wierzcholkow[i]*r;
  }
}
void Przeszkoda_prostopadloscian::Postaw(){
  this->Obrot(90, os_ox);
}
