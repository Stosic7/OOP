#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "Kvadar.h"
#include "Valjak.h"
#include "Polica.h"

void Polica::zauzmiMem(int _maxEl){
	top = 0;
	maxEl = _maxEl;

	niz = new Akvarijum * [maxEl];
	for (int i = 0; i < maxEl; i++)
		niz[i] = nullptr;
}

void Polica::oslobodiMem(){
	if (niz != nullptr)
		for (int i = 0; i < maxEl; i++)
			if (niz[i] != nullptr)
				delete niz[i];

	delete[] niz;
}

Polica::Polica(){
	niz = nullptr;
	top = maxEl = 0;
}

Polica::Polica(int _maxEl){
	zauzmiMem(_maxEl);
}

Polica::~Polica(){
	oslobodiMem();
}

void Polica::Add(Akvarijum* a){
	if (top < maxEl)
		niz[top++] = a;
}

Polica::Polica(const Polica& og){
	zauzmiMem(og.maxEl);
	for (int i = 0; i < og.top; i++)
	{
		if (typeid(*og.niz[i]) == typeid(Valjak))
			Add(new Valjak(*dynamic_cast<Valjak*>(og.niz[i])));
		else
			Add(new Kvadar(*dynamic_cast<Kvadar*>(og.niz[i])));
	}
}

double Polica::UkupnaPovrsinaStakla(){
	double suma = 0;
	for (int i = 0; i < top; i++) {
		suma += niz[i]->vratiPovrsinu();
	}

	return suma;
}

double Polica::UkupnaZapremina(){
	double suma = 0;
	for (int i = 0; i < top; i++) {
		suma += niz[i]->vratiZapreminu();
	}

	return suma;
}

Polica* Polica::PrebacitiAkvarijume(const char* tip){
	Polica* novaPolica = new Polica(maxEl);
	for (int i = 0; i < top; i++) {
		if (niz[i] != nullptr && strcmp(niz[i]->vratiTip(), tip) == 0) {
			novaPolica->Add(niz[i]);
			niz[i] = nullptr;
		}
	}
	return novaPolica;
}

void Polica::Min(int* ind, Akvarijum** pmin) const{
	if (top == 0) {
		*pmin = nullptr;
		*ind = -1;
		return;
	}

	*pmin = niz[0];
	*ind = 0;
	for (int i = 1; i < top; i++) {
		if (niz[i] != nullptr && niz[i]->koeficijentFigure() < (*pmin)->koeficijentFigure()) {
			*pmin = niz[i];
			*ind = i;
		}
	}
}

ostream& operator<<(ostream& izlaz, const Polica& p){
	for (int i = 0; i < p.maxEl; i++)
		if (p.niz[i] != nullptr)
			p.niz[i]->prikazi(izlaz);
	return izlaz;
}
