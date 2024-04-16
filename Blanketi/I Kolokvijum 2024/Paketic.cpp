#include <iostream>
#include <fstream>
#include "Paketic.h"
#include "Cokolada.h"
#include "Igracka.h"


using namespace std;

void Paketic::zauzmiMem(int _maxEl)
{

	top = 0;
	maxEl = _maxEl;

	niz = new Poklon * [maxEl];
	for (int i = 0; i < maxEl; i++)
		niz[i] = nullptr;

}

void Paketic::oslobodimem()
{

	if (niz != nullptr)
		for (int i = 0; i < maxEl; i++)
			if (niz[i] != nullptr)
				delete niz[i];

	delete[] niz;

}

Paketic::Paketic()
{

	niz = nullptr;
	top = maxEl = 0;

}

Paketic::Paketic(int _maxEl)
{

	zauzmiMem(_maxEl);

}

Paketic :: ~Paketic()
{

	oslobodimem();

}

void Paketic::Add(Poklon* p)
{

	if (top < maxEl)
		niz[top++] = p;

}

Paketic::Paketic(const Paketic& og)
{

	zauzmiMem(og.maxEl);
	for (int i = 0; i < og.top; i++)
	{
		if (typeid(*og.niz[i]) == typeid(Cokolada))
			Add(new Cokolada(*dynamic_cast<Cokolada*>(og.niz[i])));
		else
			Add(new Igracka(*dynamic_cast<Igracka*>(og.niz[i])));
	}
} //OVO

Paketic Paketic :: operator+(const Paketic p)
{

	Paketic novi(maxEl + p.maxEl);

	for (int i = 0; i < maxEl; i++)
	{
		if (typeid(*niz[i]) == typeid(Cokolada))
			novi.Add(new Cokolada(*dynamic_cast<Cokolada*>(niz[i])));
		else
			novi.Add(new Igracka(*dynamic_cast<Igracka*>(niz[i])));
	}

	for (int i = 0; i < p.maxEl; i++)
	{
		if (typeid(*p.niz[i]) == typeid(Cokolada))
			novi.Add(new Cokolada(*dynamic_cast<Cokolada*>(p.niz[i])));
		else
			novi.Add(new Igracka(*dynamic_cast<Igracka*>(p.niz[i])));
	}

	return novi;

} // OVO

void Paketic::Save(const char* filename)
{

	ofstream izlaz(filename);
	if (izlaz.good())
		izlaz << *this;
	izlaz.close();

}

Poklon* Paketic::Max() const
{

	Poklon* max = niz[0];
	for (int i = 1; i < top; i++)
		if (niz[i]->vratiBrojMasnica() > max->vratiBrojMasnica())
			max = niz[i];

	return max;

}

void Paketic::RemoveMinimum(Poklon** p)
{

	if (top == 0)
		return;

	int min = 0;
	for (int i = 1; i < top; i++)
		if (niz[i]->vratiBrojMasnica() < niz[i]->vratiBrojMasnica())
			min = i;

	*p = niz[min];

	for (int i = min; i < top - 1; i++)
		niz[i] = niz[i + 1];

	niz[top - 1] = *p;
	top--;

}

ostream& operator<<(ostream& izlaz, const Paketic& p)
{
	for (int i = 0; i < p.maxEl; i++)
		if (p.niz[i] != nullptr)
			p.niz[i]->prikazi(izlaz);
	return izlaz;
}
