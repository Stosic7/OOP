#include <iostream>
#include <fstream>
#include "Valjak.h"

using namespace std;

Valjak::Valjak() : Akvarijum(){
	r = h = 0.0;
}

Valjak::Valjak(double _r, double _h, const char* _tip, bool _poklopac) : Akvarijum(_tip, _poklopac){
	r = _r;
	h = _h;
}

Valjak::Valjak(const Valjak& og) : Akvarijum(og){
	r = og.r;
	h = og.h;
}

void Valjak::prikazi(ostream& izlaz) const{
	Akvarijum::prikazi(izlaz);
	izlaz << "Poluprecnik: " << r << "\nVisina: " << h << endl;
	izlaz << endl;
}

double Valjak::vratiPovrsinu() const{
	return (2*r*3.14*(r + h));
}

double Valjak::vratiZapreminu() const{
	return ((r*r)*3.14*h);
}

double Valjak::koeficijentFigure() const{
	return (vratiPovrsinu()/vratiZapreminu());
}
