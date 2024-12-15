#define _CRT_SECURE_NO_WARNINGS
#include "Figura.h"
#include <iostream>
#include <fstream>

using namespace std;

Figura::Figura(){
	boja = nullptr;
}

Figura::Figura(const char* _boja){
	boja = new char[strlen(_boja) + 1];
	strcpy(boja, _boja);
}

Figura::~Figura(){
	if (boja != nullptr)
		delete[] boja;
}

Figura::Figura(const Figura& og){
	boja = new char[strlen(og.boja) + 1];
	strcpy(boja, og.boja);
}

void Figura::prikazi(ostream& izlaz) const{
	cout << "Boja: " << boja << endl;
}

ostream& operator<<(ostream& izlaz, const Figura& f){
	f.prikazi(izlaz);

	return izlaz;
}
