#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class Akvarijum{
protected:
	char* tip;
	bool poklopac; // true - ima, false - nema

public:
	Akvarijum();
	Akvarijum(const char* _tip, bool _poklopac);
	virtual ~Akvarijum();
	Akvarijum(const Akvarijum& og);

	virtual void prikazi(ostream& izlaz) const;
	friend ostream& operator<<(ostream& izlaz, const Akvarijum& a);

	const char* vratiTip() { return tip; }
	bool vratiBool() { return poklopac; }

	virtual double vratiPovrsinu() const = 0;
	virtual double vratiZapreminu() const = 0;
	virtual double koeficijentFigure() const = 0;

};

