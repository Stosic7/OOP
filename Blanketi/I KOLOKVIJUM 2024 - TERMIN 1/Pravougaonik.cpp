#include "Pravougaonik.h"
#include <iostream>
#include <fstream>

Pravougaonik::Pravougaonik() : Figura(){
	a = b = 0;
}

Pravougaonik::Pravougaonik(double _a, double _b, const char* _boja) : Figura(_boja){
	a = _a;
	b = _b;
}

Pravougaonik::Pravougaonik(const Pravougaonik& og){
	a = og.a;
	b = og.b;
}

void Pravougaonik::prikazi(ostream& izlaz) const{
	Figura::prikazi(izlaz);
	izlaz << "a: " << a << "\nb: " << b << endl;
	izlaz << endl;	
}

double Pravougaonik::vratiObim() const{
	return (2*(a+b));
}

double Pravougaonik::vratiPovrsinu() const{
	return (a*b);
}

double Pravougaonik::koeficijentFigure() const{
	return (vratiPovrsinu() / vratiObim());
}
