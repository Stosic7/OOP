#pragma once
#include <iostream>
#include <fstream>
#include "Figura.h"
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

class Kolekcija
{

private:

	Figura** niz;
	int top;
	int maxEl;

	void zauzmimem(int _maxEl);
	void oslobodimem();

public:

	Kolekcija();
	Kolekcija(int _maxEl);
	~Kolekcija();

	void Add(Figura* f);
	void vratiPovrsinu();
	void vratiObim();
	void sortirajObim();
	void Save(const char* filename);

	void ispisi(ostream& izlaz) const;
	friend ostream& operator<<(ostream& os, const Kolekcija& k);

};
