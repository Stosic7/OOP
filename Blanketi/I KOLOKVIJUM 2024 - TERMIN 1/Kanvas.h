#pragma once
#include <iostream>
#include <fstream>
#include "Figura.h"

class Kanvas{
	Figura** niz;
	int top;
	int maxEl;

	void zauzmiMem(int _maxEl);
	void oslobodiMem();

public:
	Kanvas();
	Kanvas(int _maxEl);
	~Kanvas();
	Kanvas(const Kanvas& og);

	int BrojFigura() { return maxEl; }

	void Add(Figura* f);
	double UkupnaPovrsina() const;
	double UkupanObim() const;
	Kanvas* PrebacitiPoBoji(const char* boja);
	void Max(Figura** pmax, int* ind) const;

	friend ostream& operator<<(ostream& izlaz, const Kanvas& k);
};

