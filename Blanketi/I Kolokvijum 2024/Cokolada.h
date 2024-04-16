#pragma once
#include <iostream>
#include <fstream>
#include "Poklon.h"

using namespace std;

class Cokolada : public Poklon
{
private:
	int procenatKakaa;

public:
	Cokolada();
	Cokolada(int _cena, double _brojMasnica, int _procenatKakaa);
	Cokolada(const Cokolada& og);
	~Cokolada() {}

	void prikazi(ostream& izlaz) const;

	int vratiBrojMasnica() const;
};
