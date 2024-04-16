#include <iostream>
#include <fstream>
#include "Cokolada.h"

using namespace std;

Cokolada::Cokolada() : Poklon()
{
	procenatKakaa = 0;
}

Cokolada::Cokolada(int _cena, double _brojMasnica, int _procenatKakaa) : Poklon(_cena, _brojMasnica)
{

	procenatKakaa = _procenatKakaa;

}

Cokolada::Cokolada(const Cokolada& og) : Poklon(og)
{
	procenatKakaa = og.procenatKakaa;
}

void Cokolada::prikazi(ostream& izlaz) const
{
	Poklon::prikazi(izlaz);
	izlaz << "Procenat kakaa: " << procenatKakaa << endl;
	izlaz << endl;
}

int Cokolada::vratiBrojMasnica() const
{
	return 2 * brojMasnica;
}
