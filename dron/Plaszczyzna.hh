#ifndef PLASZCZYZNA_HH
#define PLASZCZYZNA_HH

/*!
 * \file
 * \brief Definicja klasy Plaszczyzna
 *
 * Plik zawiera definicje klasy Plaszczyzna
 */


/*!
 * \brief Modeluje plaszczyzne jako przeszkode
 *
 * Dziedziczy z klasy bryla zeby miec tablice wierzcholkow potrzebna do
 przeszkody
 */
#include "Bryla.hh"
class Plaszczyzna : public Bryla{
public:
/*!
 * \brief rysowanie plaszczyzny
 */
void rysuj(std::shared_ptr<drawNS::Draw3DAPI> kpi);
/*!
 * \brief wczytanie z pliku
 */
void loadfromfile(string plik);
/*!
 * \brief przesuniecie o wektor
 */
  void PrzesunOWektor(Wektor3D W);
/*!
 * \brief zwracanie punktow wektor
 */
  int zwroc_punkty(){
    return Tablica_wierzcholkow.size();
  }
};

#endif
