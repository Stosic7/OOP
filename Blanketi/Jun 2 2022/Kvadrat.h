#pragma once
#include <iostream>
#include <fstream>
#include "Figura.h"

using namespace std;

class Kvadrat : public Figura
{

private:

	double stranica;

public:

	Kvadrat();
	Kvadrat(double _x, double _y, double _stranica);
	~Kvadrat() {}
	Kvadrat(const Kvadrat& og);

	double vratiP() { return pow(stranica, 2); };
	double vratiO() { return (4 * stranica); }
	double getSirina() { return stranica; }
	double getVisina() { return stranica; }

	void ispisi(ostream& izlaz) const;
	void upisi(istream& ulaz);
};
