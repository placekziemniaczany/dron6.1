#ifndef PRZESZKODA_HH
#define PRZESZKODA_HH
/*!
 * \file
 * \brief Definicja klasy przeszkoda
 *
 * Plik zawiera definicje interfejsu przeszkody oraz klasy pochodne od niej
 */
#include "linia.hh"
#include "Prostopadloscian.hh"
#include "Plaszczyzna.hh"

class Dron;
/*!
 * \brief Modeluje przeszkode
 *
 * Modeluje drona, czyli jego kszta³t (3 bryly), cechy (kat nachylenia)
 * oraz wszystkie czynnoœci, które mo¿e wykonaæ.
 */
class Przeszkoda{
public:
  /*!
 * \brief metoda wirtualna kolizja
 */
virtual bool kolizja(std::shared_ptr<Dron> D)=0;
  /*!
 * \brief metoda wirtualna dodwania przeszkody
 */
virtual void dodaj_przeszkode(Wektor3D pocz)=0;
};
/*!
 * \brief Modeluje przeszkode prostopadloscienna
 *
 * Dziedziczy z klas przeszkoda i prostopadloscian, modeluje przeszkode prostopadloscienna
 */
class Przeszkoda_prostopadloscian : public Przeszkoda, public Prostopadloscian{
public:
      /*!
 * \brief metoda kolizja
 */
    bool kolizja(std::shared_ptr<Dron> D)override;
      /*!
 * \brief metoda dodwania przeszkody
 */
    void dodaj_przeszkode(Wektor3D pocz)override;
         /*!
 * \brief metoda skalowania
 */
  void skaluj(double r);
       /*!
 * \brief metoda obracania przeszkody pionowo
 */
  void Postaw();
};

/*!
 * \brief Modeluje przeszkode wode
 *
 * Dziedziczy z klas przeszkoda i plasczyzna, modeluje przeszkode jako powierzchnie
 */
class Woda : public Przeszkoda, public Plaszczyzna {
public:
     /*!
 * \brief metoda kolizja
 */
    bool kolizja(std::shared_ptr<Dron> D)override;
      /*!
 * \brief metoda dodwania przeszkody
 */
void dodaj_przeszkode(Wektor3D pocz)override;

};
#endif // PRZESZKODA_HH
