#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class Poklon
{

protected:

	double cena;
	int brojMasnica;

public:

	Poklon();
	Poklon(double _cena, int _brojMasnica);
	virtual ~Poklon();
	Poklon(const Poklon& og);

	virtual void prikazi(ostream& izlaz) const;
	friend ostream& operator<<(ostream& izlaz, const Poklon& p);

	virtual int vratiBrojMasnica() const = 0;

};
