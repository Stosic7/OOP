#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class Figura
{

protected:

	double x, y;

public:

	Figura();
	Figura(double _x, double _y);
	virtual ~Figura() {}
	Figura(const Figura& og);

	virtual void upisi(istream& ulaz) = 0;
	virtual void ispisi(ostream& izlaz) const = 0;

	virtual double vratiP() = 0;
	virtual double vratiO() = 0;
	virtual double getSirina() = 0;
	virtual double getVisina() = 0;

	friend ostream& operator<<(ostream& os, const Figura& f);

};
