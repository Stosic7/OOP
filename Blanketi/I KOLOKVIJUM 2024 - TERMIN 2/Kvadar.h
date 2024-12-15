#pragma once
#include <iostream>
#include <fstream>
#include "Akvarijum.h"

using namespace std;

class Kvadar : public Akvarijum{
private:
	double a, b, c;

public:
	Kvadar();
	Kvadar(double _a, double _b, double _c, const char* _tip, bool _poklopac);
	~Kvadar() {}
	Kvadar(const Kvadar& og);

	void prikazi(ostream& izlaz) const;

	double vratiPovrsinu() const;
	double vratiZapreminu() const;
	double koeficijentFigure() const;
};

