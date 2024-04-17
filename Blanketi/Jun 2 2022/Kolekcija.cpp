#include <iostream>
#include <fstream>
#define _CRT_SECURE_NO_WARNINGS
#include "Kolekcija.h"

using namespace std;

void Kolekcija::zauzmimem(int _maxEl)
{

	top = 0;
	maxEl = _maxEl;

	niz = new Figura * [maxEl];
	for (int i = 0; i < maxEl; i++)
	{

		niz[i] = nullptr;

	}

}

void Kolekcija::oslobodimem()
{

	if (niz != nullptr)
	{

		for (int i = 0; i < maxEl; i++)
		{

			if (niz[i] != nullptr)
			{

				delete niz[i];

			}

		}

		delete[] niz;

	}

}

Kolekcija::Kolekcija()
{

	niz = nullptr;
	top = maxEl = 0;

}

Kolekcija::Kolekcija(int _maxEl)
{

	zauzmimem(_maxEl);

}

Kolekcija :: ~Kolekcija()
{

	oslobodimem();

}

void Kolekcija::Add(Figura* f)
{

	if (top < maxEl)
		niz[top++] = f;
	else
	{

		int noviMax = maxEl + (maxEl / 2);
		Figura** temp = new Figura * [noviMax];
		
		for (int i = 0; i < noviMax; i++)
			temp[i] = nullptr;

		for (int i = 0; i < top; i++)
		{

			temp[i] = niz[i];

		}

		delete[] niz;

		maxEl = noviMax;
		niz = temp;

		niz[top++] = f;

	}

}

void Kolekcija::vratiPovrsinu()
{
	for (int i = 0; i < top; i++)
		cout << niz[i]->vratiP() << endl;
}

void Kolekcija::vratiObim()
{
	for (int i = 0; i < top; i++)
		cout << niz[i]->vratiO() << endl;
}

void Kolekcija::sortirajObim()
{
	int min;
	for (int i = 0; i < top - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < top; j++)
			if (niz[j]->vratiO() < niz[i]->vratiO())
				min = j;
		if (min != i)
			swap(niz[min], niz[i]);
	}
}

void Kolekcija::Save(const char* filename)
{

	ofstream izlaz(filename);

	if (izlaz.good())
		izlaz << *this;

	izlaz.close();
}

void Kolekcija::ispisi(ostream& izlaz) const
{
	for (int i = 0; i < maxEl; i++)
	{
		if (niz[i] != nullptr)
		{
			niz[i]->ispisi(izlaz);
			izlaz << endl;
		}
		else
			izlaz << "prazno mesto" << endl;
	}
}

ostream& operator<<(ostream& os, const Kolekcija& k)
{

	k.ispisi(os);

	return os;

}
