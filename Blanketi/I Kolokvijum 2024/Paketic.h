#pragma once
#include <iostream>
#include <fstream>
#include "Poklon.h" // include za poklon

using namespace std;

class Paketic // ovde ne treba da se naseledjuje Poklon, a zasto? Jer se ovde ne koriste funkcije i kosntruktori iz Poklona, vec se koristi Poklon kao tip promenljive (kao niz Poklona)
{
// kad se ne naglasi pravo pristupa, podrazumeva se private
	Poklon** niz; // ovde mora ** jer se prvo "otpakuje" prvi * da se protoumaci jel CCokolada ili Igrakca, a drugi * da bi "dopreo" do osnovne klase Poklon, kao da ga duplo otpakuje
	int top; // vrh niza, oznacava na kojoj poziciji je poslednji dodat element u nizu Poklon** niz
	int maxEl; // ovo je maksimalni broj elemenata niza Poklon** niz, top oznacava poziciju poslednjeg dodatog elementa, a maxEl oznacava koliko maks el. moze da ima niz, u sustini, top se menja, ovo se ne menja

	void zauzmiMem(int _maxEl); // funkcija koja zauzima potrebnu memoriju
	void oslobodimem(); // funkcija koja oslobadja zauzetu memoriju

public:

	Paketic(); // default konstruktor
	Paketic(int _maxEl); // custom konstruktor kome ce biti prosledjena maksimalna vrednost koju niz moze da ima
	~Paketic(); // destruktor
	Paketic(const Paketic& og); // copy konstruktor

	int BrojPoklona() const { return maxEl; } // funkcija koja vraca brojPoklona, to je jednako maxEl promenljivoj, pa smo je odmah implementirali ovde

	void Add(Poklon* p); // funkcija za doavanje u niz, prima kao argument p tipa Poklon*, jedna * je zato sto treba samo jednom da se otpakuje, samo nas zanima jel Cokolada ili Igracka
	Paketic operator+(const Paketic p); // operator +, ovde nema &Paketic jer se sve dodaje unutar ove klase, dva paketica se dodaju, nema zbog cega da uzme adresu(&), pa zato samo Paketic
	void Save(const char* filename); // funkcija koja cuva niz u fajl
	Poklon* Max() const; // vraca Max(), self explanatory 
	void RemoveMinimum(Poklon** p); // removeMinimum(Poklon** p), self explanatory 

	friend ostream& operator<<(ostream& izlaz, const Paketic& p); // ovde mora operator <<, nije nasledjena klasa

};
