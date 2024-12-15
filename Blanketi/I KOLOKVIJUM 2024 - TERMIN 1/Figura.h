#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class Figura{
protected:
	char* boja;

public:
	Figura();
	Figura(const char* _boja);
	virtual ~Figura();
	Figura(const Figura& og);

	virtual void prikazi(ostream& izlaz) const;
	friend ostream& operator<<(ostream& izlaz, const Figura& f);

	const char* vratiBoju() { return boja; }

	virtual double koeficijentFigure() const = 0;
	virtual double vratiObim() const = 0;
	virtual double vratiPovrsinu() const = 0;
};

