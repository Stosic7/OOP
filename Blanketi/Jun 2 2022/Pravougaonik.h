#pragma once
#include <iostream>
#include <fstream>
#include "Figura.h"

using namespace std;

class Pravougaonik : public Figura
{

private:

	double visina, sirina;

public:

	Pravougaonik();
	Pravougaonik(double _x, double _y, double _visina, double _sirina);
	~Pravougaonik() {}
	Pravougaonik(const Pravougaonik& og);

	double vratiP() { return visina * sirina; };
	double vratiO() { return (2 * visina + 2 * sirina); }
	double getSirina() { return sirina; }
	double getVisina() { return visina; }

	void ispisi(ostream& izlaz) const;
	void upisi(istream& ulaz);

};
