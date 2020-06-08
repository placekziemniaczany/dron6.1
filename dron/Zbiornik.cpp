#include "Zbiornik.hh"
using namespace std;
using drawNS::APIGnuPlot3D;
using drawNS::Point3D;
/*!
 * Funkcja wyswietlajaca menu
 *
 * Funkcja po prostu wyswietla co mozna zrobic z dronem, to znaczy
 * za co odpowiadaja poszczegolne litery kiedy sie je wpisze
 */
void Zbiornik::WyswietlMenu(){
cout<<"\t CENTRUM STEROWANIA DRONEM PODWODNYM! " <<endl;
    cout << "p -> Plywanie" << endl;
    cout << "o -> Obrot: "<<endl;
    cout << "w -> Ponowne wyswietlenie menu" << endl;
    cout << "c -> wybierz drona" << endl;
    cout << "d -> dodaj drona" << endl;
    cout << "q -> dodaj przeszkode" <<endl;
    cout << "l -> pokaz ilosc obiektow"<<endl;
    cout << "k -> Zakonczenie dzialania programu" << endl;
}
/*!
 * Funkcja obslugujaca ruch drona i animujaca go
 *
 * Funkcja prosi na poczatku uzytkownika o wpisanie mozliwego znaku ktory odpowiada za
 * dana akcje. Sprawdzana jest poprawnosc wpisanego mozliwego znaku
 *
 *\param kpi - wskaznik do programu rysowania gnuplot
 */
void Zbiornik::Menu(std::shared_ptr<drawNS::Draw3DAPI> kpi){
    std::vector<std::shared_ptr<Przeszkoda> > kolekcja_przeszkod;
    std::vector<std::shared_ptr<Dron> > kolekcja_Dronow;
    kolekcja_Dronow.push_back(D);
   
    this->Tafla=std::shared_ptr<Woda> (new Woda);
    this->Dno=std::shared_ptr<Woda> (new Woda);
    this->Tafla->loadfromfile("tafla.txt");
    kolekcja_przeszkod.push_back(Tafla);
    this->Dno->loadfromfile("Dno.txt");
    kolekcja_przeszkod.push_back(Dno);
    this->P=std::shared_ptr<Przeszkoda_prostopadloscian>(new Przeszkoda_prostopadloscian);
    double skala, g;
    int aktob;
    int stwob;
    char odp;
    bool kontrola;
    stwob = this->D->zwroc_punkty()+this->Dno->zwroc_punkty()+this->Tafla->zwroc_punkty();
    aktob = this->D->zwroc_punkty()+this->Dno->zwroc_punkty()+this->Tafla->zwroc_punkty();
    Wektor3D poczatek;
    char znak;
    double kat, odleglosc;
    while(znak != 'k'){
    cin>>znak;
    switch(znak){
    case 'p':
        cout<<"Na jaką odleglosc ma plynac? "<<endl;
        cin>>odleglosc;
        cout<<"Podaj kat wznoszenia/opadania drona "<<endl;
        cin>>kat;
	for(auto elem : kolekcja_przeszkod){
	  if(elem->kolizja(D)){
	    cerr<<"UWAGA KOLIZJA!"<<endl;
	    kontrola = true;
	  }
	}
	if (kontrola == false){
	    for(g = 0; g<odleglosc/2; g++){
	  stwob=stwob+this->D->zwroc_punkty();
	  this->D->Plyn(g, kat, kpi);
	    }
	}
	break;
    case 'o':
        cout<<"Podaj kat na jaki chcesz obrocic drona "<<endl;
        cin>>kat;
        for(double i = 0; i<2*kat; i++){
	  stwob=stwob+this->D->zwroc_punkty();
        this->D->Obrot(i, kpi);
    }
    break;
    case 'q':
      P=std::shared_ptr<Przeszkoda_prostopadloscian> (new Przeszkoda_prostopadloscian);
      this->P->loadfromfile("korpus.txt");
      kolekcja_przeszkod.push_back(P);
      cout<<"Podaj skale"<<endl;
      cin>>skala;
      this->P->skaluj(skala);
      P->rysuj(kpi);
      cout<<"Czy chcesz postawic przeszkode? T/N"<<endl;
      cin>>odp;
      if(odp=='T'){
	this->P->Postaw();
      }
      P->rysuj(kpi);
      cout<<"Gdzie chcesz umiescic przeszkode (wektor)?"<<endl;
							  cin>>poczatek;
	    P->dodaj_przeszkode(poczatek);
	    P->rysuj(kpi);
	    stwob=stwob+this->D->zwroc_punkty();
				      aktob=aktob+this->D->zwroc_punkty();
	    break;
    case 'l':
	    cout<<"Ilosc aktywnych obiektow to "<<aktob<<endl;
							 cout<<"Ilosc stworzonych obiektow to " <<stwob<<endl;
    case 'w':
        this->WyswietlMenu();
        break;
    case 'k':
        cout<<"Koniec pracy z programem!"<<endl;
        exit(0);
        case 'c':
           unsigned int indx;
            cout<<"Wybierz drona. Dostepne drony to"<<endl;
            for(unsigned int i = 0; i<kolekcja_Dronow.size(); i++){
	      cout<<i<<" ze srodkiem w "<<kolekcja_Dronow[i]->P.srodek<<endl;
            }
            cin>>indx;
	    while(cin.fail()){
	      cerr<<"Prosze podac prawidlowy index drona"<<endl;
	      cin.clear();
	      cin.ignore(10000, '\n');
	      cin>>indx;
	    }
	      while (indx > kolekcja_Dronow.size() || indx<0){
                cerr<<"Prosze podac prawidlowy index drona"<<endl;
cin.clear();
	      cin.ignore(10000, '\n');
	      cin>>indx;
	      }
        this->D = kolekcja_Dronow[indx];
cout<<"Wybrales drona z indeksem "<<indx<<endl;
        break;
    case 'd':
        Wektor3D pocz;
	std::shared_ptr<Dron> nowy;
	nowy = std::shared_ptr <Dron> (new Dron);
        cout<<"Podaj srodek drona"<<endl;
        cin>>pocz;
        nowy->dodaj_przeszkode(pocz);
        kolekcja_Dronow.push_back(nowy);
        kolekcja_przeszkod.push_back(nowy);
        nowy->rysuj(kpi);
					  stwob=stwob+this->D->zwroc_punkty();
				    aktob=aktob+this->D->zwroc_punkty();
	cout<<"Pamietaj!! Aby sterowac nowym dronem, wybierz opcje c->wybierz drona"<<endl;
        break;
    }
}
}

/*!
 * Funkcja zbierajaca wszystkie elementy zbiornika razem
 *
 * Funkcja inicjuje program gnuplot o danych rozmiarach, rysuje poczatkowa pozycje drona
 * rysuje takze dno oraz powierzchnie wody, wyswietla menu poczatkowe oraz uruchamia funkcje
 * menu odpowiadajaca za ruch drona
 *
 */

void Zbiornik::Scena(){

  std::shared_ptr<drawNS::Draw3DAPI> api (new APIGnuPlot3D(-30,30,-30,30,-30,30,0));
  this->D->rysuj(api);
  this->D->rysuj(api);
  api->draw_surface(vector<vector<Point3D>>{{
	drawNS::Point3D(-30,-30,28), drawNS::Point3D(-30,0,30), drawNS::Point3D(-30,30,28)},{
	drawNS::Point3D(-20,-30,30), drawNS::Point3D(-20,0,28), drawNS::Point3D(-20,30,30)},{
	drawNS::Point3D(-10,-30,28), drawNS::Point3D(-10,0,30), drawNS::Point3D(-10,30,28)},{
	drawNS::Point3D(0,-30,30), drawNS::Point3D(0,0,28), drawNS::Point3D(0,30,30)}, {
	drawNS::Point3D(10,-30,28), drawNS::Point3D(10,0,30), drawNS::Point3D(10,30,28)},{
	drawNS::Point3D(20,-30,30), drawNS::Point3D(20,0,28), drawNS::Point3D(20,30,30)},{
	drawNS::Point3D(30,-30,28), drawNS::Point3D(30,0,30), drawNS::Point3D(30,30,28)}
    },"blue");
  api->draw_surface(vector<vector<Point3D>>{{
	drawNS::Point3D(-30,-30,-30), drawNS::Point3D(-30,0,-30), drawNS::Point3D(-30,30,-30)},{
	drawNS::Point3D(-20,-30,-30), drawNS::Point3D(-20,0,-30), drawNS::Point3D(-20,30,-30)},{
	drawNS::Point3D(-10,-30,-30), drawNS::Point3D(-10,0,-30), drawNS::Point3D(-10,30,-30)},{
	drawNS::Point3D(0,-30,-30), drawNS::Point3D(0,0,-30), drawNS::Point3D(0,30,-30)}, {
	drawNS::Point3D(10,-30,-30), drawNS::Point3D(10,0,-30), drawNS::Point3D(10,30,-30)},{
	drawNS::Point3D(20,-30,-30), drawNS::Point3D(20,0,-30), drawNS::Point3D(20,30,-30)},{
	drawNS::Point3D(30,-30,-30), drawNS::Point3D(30,0,-30), drawNS::Point3D(30,30,-30)}
    },"blue");
  this->WyswietlMenu();
  this->Menu(api);
}
