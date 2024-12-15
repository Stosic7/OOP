#pragma once
#include <iostream>
#include <fstream>
#include "Figura.h"
class Pravougaonik : public Figura{
private:
	double a, b;

public:
	Pravougaonik();
	Pravougaonik(double _a, double _b, const char* _boja);
	~Pravougaonik() {}
	Pravougaonik(const Pravougaonik& og);

	void prikazi(ostream& izlaz) const;

	double vratiObim() const;
	double vratiPovrsinu() const;
	double koeficijentFigure() const;
};

