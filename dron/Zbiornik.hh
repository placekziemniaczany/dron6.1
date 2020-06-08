#ifndef SCENA_HH
#define SCENA_HH
/*!
 * \file
 * \brief Definicja klasy Zbiornik
 *
 * Plik zawiera definicjê klasy zbiornik
 */
#include <iostream>
#include "dron.hh"
#include "Przeszkoda.hh"
/*!
 * \brief Modeluje zbiornik zawierajacy elementy tam sie znajdujace
 *
 * Posiada metody odpowiadajace za dzialanie programu do obslugi drona
 *
 */
class Zbiornik{
/*!
 * wskaznik na drona
 */
   std::shared_ptr<Dron> D;
   /*!
 * wskaznik na przeszkode prostopadloscienna
 */
   std::shared_ptr<Przeszkoda_prostopadloscian> P;
   /*!
 * wskaznik na tafle
 */
  std::shared_ptr<Woda> Tafla;
  /*!
 * wskaznik na dno
 */
  std::shared_ptr<Woda> Dno;
public:
    Zbiornik(){D=std::shared_ptr <Dron>(new Dron);}
/*!
 * Metoda wyswietlajaca menu
 */
    void WyswietlMenu();
/*!
 * Metoda obslugujaca menu
 */
    void Menu(std::shared_ptr<drawNS::Draw3DAPI> kpi);
    /*!
 * Metoda obslugujaca scene graficzna i interfejs uzytkownika
 */
    void Scena();
};
#endif // SCENA_HH
