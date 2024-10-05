#pragma once
#include <iostream>
#include <fstream>
#include "Poklon.h" // include za Pokloj

using namespace std;

class Cokolada : public Poklon // nasledjuje apstraktnu klasu Poklon
{
private: // private pravo pristupa
	int procenatKakaa;

public: // public pravo pristupa
	Cokolada(); // default konstruktor
	Cokolada(int _cena, double _brojMasnica, int _procenatKakaa); // custom konstruktor koji ima parametre iz osnovne klase Poklon + svoje parametre
	Cokolada(const Cokolada& og); // copy konstruktor
	~Cokolada() {} // desturktor

	void prikazi(ostream& izlaz) const; // overriduje funkciju iz osnovne klase Poklon

	int vratiBrojMasnica() const; // ovde se implementira

	// ovde ne treba operator <<, jer se operatori NE NASLEDJUJU. Koristimo funkciju prikazi koja ce biti overirdovana (updatovana) u zavisnosti koji objekat se pravi, pa ce ona kao takva
	// pozvati biti pozvana u operatoru << koji je definisan u Poklon.cpp
};
