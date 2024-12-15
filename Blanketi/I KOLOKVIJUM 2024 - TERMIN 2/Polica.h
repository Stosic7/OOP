#pragma once
#include <iostream>
#include <fstream>
#include "Akvarijum.h"

using namespace std;

class Polica{
	Akvarijum** niz;
	int top;
	int maxEl;

	void zauzmiMem(int _maxEl);
	void oslobodiMem();

public:
	Polica();
	Polica(int _maxEl);
	~Polica();
	Polica(const Polica& og);

	int BrojAkvarijuma() { return maxEl; }

	void Add(Akvarijum* a);
	double UkupnaPovrsinaStakla();
	double UkupnaZapremina();
	Polica* PrebacitiAkvarijume(const char* tip);
	void Min(int* ind, Akvarijum** pmin) const;

	friend ostream& operator<<(ostream& izlaz, const Polica& p);

};

