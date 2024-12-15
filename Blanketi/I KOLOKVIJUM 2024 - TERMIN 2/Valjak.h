#pragma once
#include <iostream>
#include <fstream>
#include "Akvarijum.h"

using namespace std;

class Valjak : public Akvarijum{
private:
	double r, h;

public:
	Valjak();
	Valjak(double _r, double _h, const char* _tip, bool _poklopac);
	~Valjak() {}
	Valjak(const Valjak& og);

	void prikazi(ostream& izlaz) const;

	double vratiPovrsinu() const;
	double vratiZapreminu() const;
	double koeficijentFigure() const;
};

