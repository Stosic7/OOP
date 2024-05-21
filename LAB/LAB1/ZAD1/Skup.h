#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class Skup
{

private:

	int brojelemenata;
	int* niz;

public:

	Skup();
	Skup(int _brojelemenata);
	~Skup();
	Skup(const Skup& og);

	inline int vratiBroj() { return brojelemenata; }

	void izbaciDuplikate();
	bool pripadnostSkupa(int el);
	void sortiraj();
	void citaj(istream& ulaz);
	void prikazi(ostream& izlaz) const;

	friend ostream& operator<<(ostream& izlaz, const Skup& s);
	friend istream& operator>>(istream& ulaz, Skup& s);

};
