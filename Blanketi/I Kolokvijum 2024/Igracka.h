#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "Poklon.h" // include za poklon, jer ova klasa treba da ga nasledi

using namespace std; // kontejnerska klasa

class Igracka : public Poklon // nasledjuje Poklon
{
private: // private pravo pristupa
	char* tipMaterijala; // dinamicka promenljiva

public:
	Igracka(); // default konstruktor
	Igracka(double _cena, int _brojMasnica, const char* _tipMaterijala); // ovaj constructor mora da ima parametre koje ima poklon + svoje parametre
	Igracka(const Igracka& og); // copy constructor
	~Igracka(); // destruktor

	void prikazi(ostream& izlaz) const; // nema virtual, jer ce samo da overriduje iz nasladjene klase

	int vratiBrojMasnica() const; // ovde implementiramo ovu funkciju

};
