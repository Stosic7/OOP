#include <iostream>
#include <fstream>
#include "Kvadrat.h"

using namespace std;

Kvadrat::Kvadrat() : Figura()
{

	stranica = 0;

}

Kvadrat::Kvadrat(double _x, double _y, double _stranica) : Figura(_x, _y)
{

	stranica = _stranica;

}

Kvadrat::Kvadrat(const Kvadrat& og) : Figura(og)
{

	stranica = og.stranica;

}

void Kvadrat::ispisi(ostream& izlaz) const
{
	izlaz << "KVADRAT" << endl << "koordinate x i y su: " << x << ", " << y << endl << "stranica je: " << stranica << endl;
}

void Kvadrat::upisi(istream& ulaz)
{
	double xx, yy, duzina;
	ulaz >> xx >> yy >> duzina;
	x = xx;
	y = yy;
	stranica = duzina;
}
