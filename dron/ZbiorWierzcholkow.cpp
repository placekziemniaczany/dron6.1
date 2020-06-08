/*!
 *  \file
 *  \brief Zawiera definicje metod klasy ZbiorWierzcholkow.
 *
 *  Zawiera definicje metod klasy ZbiorWierzcholkow, wraz
 *  z ich opisem.
 */
#include "ZbiorWierzcholkow.hh"
/*!
 * Metoda Tworzy nowy obiekt klasy \e Wektor3D, oraz
 * dodaje do niego pobrane warto�ci. Nast�pnie dziedziczon�
 * metod� \e push_back(), dodaje dany obiekt na pocz�tek tablicy \e vector.
 *
 * \param a - X'owa wsp�rz�dna wierzcho�ka
 * \param b - Y'owa wsp�rz�dna wierzcho�ka
 * \param c - Z'owa wsp�rz�dna wierzcho�ka
 */
void ZbiorWierzcholkow::DodajWierzcholek(double a, double b, double c) {
Wektor3D nowy;
nowy[0] = a;
nowy[1] = b;
nowy[2] = c;
push_back(nowy);
}

