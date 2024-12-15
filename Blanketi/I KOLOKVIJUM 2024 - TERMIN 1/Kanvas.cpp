#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "Kanvas.h"
#include "Krug.h"
#include "Pravougaonik.h"

void Kanvas::zauzmiMem(int _maxEl)
{
	top = 0; 
	maxEl = _maxEl; 

	niz = new Figura * [maxEl]; 
	for (int i = 0; i < maxEl; i++) 
		niz[i] = nullptr;
}

void Kanvas::oslobodiMem()
{
	if (niz != nullptr) 
		for (int i = 0; i < maxEl; i++)  
			if (niz[i] != nullptr)
				delete niz[i];

	delete[] niz;
}

Kanvas::Kanvas()
{
	niz = nullptr;
	top = maxEl = 0;
}

Kanvas::Kanvas(int _maxEl)
{
	zauzmiMem(_maxEl);
}

Kanvas::~Kanvas()
{
	oslobodiMem();
}

void Kanvas::Add(Figura* f)
{
	if (top < maxEl)
		niz[top++] = f;
}

Kanvas::Kanvas(const Kanvas& og)
{
	zauzmiMem(og.maxEl);
	for (int i = 0; i < og.top; i++)
	{
		if (typeid(*og.niz[i]) == typeid(Krug)) 
			Add(new Krug(*dynamic_cast<Krug*>(og.niz[i])));
		else
			Add(new Pravougaonik(*dynamic_cast<Pravougaonik*>(og.niz[i])));
	}
}

double Kanvas::UkupnaPovrsina() const
{
	double suma = 0;
	for (int i = 0; i < top; i++) {
		suma += niz[i]->vratiPovrsinu();
	}

	return suma;
}

double Kanvas::UkupanObim() const
{
	double suma = 0;
	for (int i = 0; i < top; i++) {
		suma += niz[i]->vratiObim();
	}

	return suma;
}

Kanvas* Kanvas::PrebacitiPoBoji(const char* boja) {
	Kanvas* noviKanvas = new Kanvas(maxEl);
	for (int i = 0; i < top; i++) {
		if (niz[i] != nullptr && strcmp(niz[i]->vratiBoju(), boja) == 0) {
			noviKanvas->Add(niz[i]);
			niz[i] = nullptr;
		}
	}
	return noviKanvas;
}


void Kanvas::Max(Figura** pmax, int* ind) const {
	if (top == 0) {
		*pmax = nullptr;
		*ind = -1;
		return;
	}

	*pmax = niz[0];
	*ind = 0;
	for (int i = 1; i < top; i++) {
		if (niz[i] != nullptr && niz[i]->koeficijentFigure() > (*pmax)->koeficijentFigure()) {
			*pmax = niz[i];
			*ind = i;
		}
	}
}

ostream& operator<<(ostream& izlaz, const Kanvas& k)
{
	for (int i = 0; i < k.maxEl; i++)
		if (k.niz[i] != nullptr)
			k.niz[i]->prikazi(izlaz);
	return izlaz;
}
