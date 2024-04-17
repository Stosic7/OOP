#include <iostream>
#include <fstream>
#include "Pravougaonik.h"

using namespace std;

Pravougaonik::Pravougaonik() : Figura()
{

	sirina = visina = 0;

}

Pravougaonik::Pravougaonik(double _x, double _y, double _visina, double _sirina) : Figura(_x, _y)
{

	visina = _visina;
	sirina = _sirina;

}

Pravougaonik::Pravougaonik(const Pravougaonik& og) : Figura(og)
{

	visina = og.visina;
	sirina = og.sirina;

}

void Pravougaonik::ispisi(ostream& izlaz) const
{
	izlaz << "PRAVOUGAONIK" << endl << "koordinate x i y su: " << x << " " << y << endl << "sirina stranice je: " << sirina << endl << "visina je: " << visina << endl;
}

void Pravougaonik::upisi(istream& ulaz)
{
	double xx, yy, vvisina, ssirina;
	ulaz >> xx >> yy >> vvisina >> ssirina;
	x = xx;
	y = yy;
	visina = vvisina;
	sirina = ssirina;
}
