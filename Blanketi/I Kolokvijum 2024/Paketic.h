#pragma once
#include <iostream>
#include <fstream>
#include "Poklon.h"

using namespace std;

class Paketic
{

	Poklon** niz;
	int top;
	int maxEl;

	void zauzmiMem(int _maxEl);
	void oslobodimem();

public:

	Paketic();
	Paketic(int _maxEl);
	~Paketic();
	Paketic(const Paketic& og);

	int BrojPoklona() const { return maxEl; }

	void Add(Poklon* p);
	Paketic operator+(const Paketic p);
	void Save(const char* filename);
	Poklon* Max() const;
	void RemoveMinimum(Poklon** p);

	friend ostream& operator<<(ostream& izlaz, const Paketic& p);

};
