#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "Igracka.h" // include za igracku

using namespace std; // kontejnerska klasa

Igracka::Igracka() : Poklon() //  default konstruktor koji nasledjuje Poklon() konstruktor
{

	tipMaterijala = nullptr;

}

Igracka::Igracka(double _cena, int _brojMasnica, const char* _tipMaterijala) : Poklon(_cena, _brojMasnica) // custom konstruktor koji nasledjuje Poklon(_cena, _brojMasnica)
{

	tipMaterijala = new char[strlen(_tipMaterijala) + 1]; // za tipMaterijala zauzimamo novi mem prostor koji ima duzinu kao prosledjeni argument + 1
	strcpy(tipMaterijala, _tipMaterijala); // samo se kopira iz _tipMaterijala u tipMaterijala

}

Igracka::Igracka(const Igracka& og) : Poklon(og) // copy const koji nasledjuje Poklon(og)
{

	tipMaterijala = new char[strlen(og.tipMaterijala) + 1]; // isti fazon kao za konstruktor samo sto se sad uzima strlen od og.tipMaterijala
	strcpy(tipMaterijala, og.tipMaterijala); // i ovo je isto

}

Igracka::~Igracka()
{
	if (tipMaterijala != nullptr) // jel tipMaterijala ima neki karakter?
		delete[] tipMaterijala; // ako ima, obrisi ga, oslobodi memoriju
}

void Igracka::prikazi(ostream& izlaz) const // overriduje prikazi funkciju iz Poklona
{
	Poklon::prikazi(izlaz); // ovde je "prepisuje" iz poklona
	izlaz << "Tip materijala: " << tipMaterijala << endl; // ovde dodaje nove podatke u overridovanu funkciju prikazi
	izlaz << endl;
}

int Igracka::vratiBrojMasnica() const
{
	return 2 + brojMasnica; // ovo je uslov zadatka
}
