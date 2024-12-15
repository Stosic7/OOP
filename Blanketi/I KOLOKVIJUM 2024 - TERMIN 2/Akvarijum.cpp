#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "Akvarijum.h"

Akvarijum::Akvarijum(){
	tip = nullptr;
	poklopac = false;
}

Akvarijum::Akvarijum(const char* _tip, bool _poklopac){
	tip = new char[strlen(_tip) + 1];
	strcpy(tip, _tip);

	poklopac = _poklopac;
}

Akvarijum::~Akvarijum(){
	if (tip != nullptr)
		delete[] tip;
}

Akvarijum::Akvarijum(const Akvarijum& og){
	tip = new char[strlen(og.tip) + 1];
	strcpy(tip, og.tip);

	poklopac = og.poklopac;
}

void Akvarijum::prikazi(ostream& izlaz) const{
	cout << "Tip: " << tip << "\nPoklopac: " << poklopac << endl;
}

ostream& operator<<(ostream& izlaz, const Akvarijum& a){
	a.prikazi(izlaz);

	return izlaz;
}
