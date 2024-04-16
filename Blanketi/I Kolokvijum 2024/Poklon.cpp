#include <iostream>
#include <fstream>
#include "Poklon.h"

using namespace std;

Poklon::Poklon()
{
	cena = 0;
	brojMasnica = 0;
}

Poklon::Poklon(double _cena, int _brojMasnica)
{

	cena = _cena;
	brojMasnica = _brojMasnica;

}

Poklon::Poklon(const Poklon& og)
{

	cena = og.cena;
	brojMasnica = og.brojMasnica;

}

Poklon :: ~Poklon()
{}

void Poklon::prikazi(ostream& izlaz) const
{

	izlaz << "Cena: " << cena << "\nBroj masnica: " << brojMasnica << endl;

}

ostream& operator<<(ostream& izlaz, const Poklon& p)
{

	p.prikazi(izlaz);

	return izlaz;

}
