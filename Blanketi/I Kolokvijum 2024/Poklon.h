#pragma once
#include <iostream> // uvek na pocetak
#include <fstream> // uvek na pocetak

using namespace std; // kontejnerska klasa, koristi je, lakse je

class Poklon // javna klasa (apstraktna)
{

protected: // zasticeno pravo pristupa

	double cena;
	int brojMasnica;

public: // javno pravo pristupa

	Poklon(); // default konstruktor
	Poklon(double _cena, int _brojMasnica); //  custom konstruktor
	virtual ~Poklon(); // destruktor, mora biti virtuelni jer je klasa apstraktna, znaci treba da se nasledi
	Poklon(const Poklon& og); // copy konstruktor, tako ga pamti, uvek ga definises ovako, implementacija uvek ista

	virtual void prikazi(ostream& izlaz) const; // virtualna funkcija za prikaz (output)
	friend ostream& operator<<(ostream& izlaz, const Poklon& p); // operator <<, uvek se dodaje

	virtual int vratiBrojMasnica() const = 0; // virtuelna apstraktna funkcija, implementira se u naslednicima ove klase

};
