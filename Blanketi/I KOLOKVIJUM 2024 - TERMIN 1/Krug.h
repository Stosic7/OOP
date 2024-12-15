#pragma once
#include <iostream>
#include <fstream>
#include "Figura.h"
#include <math.h>

using namespace std;

class Krug : public Figura{
private:
	double r;

public:
	Krug();
	Krug(double _r, const char* _boja);
	~Krug() {}
	Krug(const Krug& og);

	void prikazi(ostream& izlaz) const;

	double vratiObim() const;
	double vratiPovrsinu() const;
	double koeficijentFigure() const;
};

