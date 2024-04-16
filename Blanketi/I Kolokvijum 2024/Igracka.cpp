#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "Igracka.h"

using namespace std;

Igracka::Igracka() : Poklon()
{

	tipMaterijala = nullptr;

}

Igracka::Igracka(double _cena, int _brojMasnica, const char* _tipMaterijala) : Poklon(_cena, _brojMasnica)
{

	tipMaterijala = new char[strlen(_tipMaterijala) + 1];
	strcpy(tipMaterijala, _tipMaterijala);

}

Igracka::Igracka(const Igracka& og) : Poklon(og)
{

	tipMaterijala = new char[strlen(og.tipMaterijala) + 1];
	strcpy(tipMaterijala, og.tipMaterijala);

}

Igracka::~Igracka()
{
	if (tipMaterijala != nullptr)
		delete[] tipMaterijala;
}

void Igracka::prikazi(ostream& izlaz) const
{
	Poklon::prikazi(izlaz);
	izlaz << "Tip materijala: " << tipMaterijala << endl;
	izlaz << endl;
}

int Igracka::vratiBrojMasnica() const
{
	return 2 + brojMasnica;
}
