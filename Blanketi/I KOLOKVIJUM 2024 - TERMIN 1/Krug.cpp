#include "Krug.h"
#include <iostream>
#include <fstream>

Krug::Krug() : Figura(){
	r = 0.0;
}

Krug::Krug(double _r, const char* _boja) : Figura(_boja){
	r = _r;
}

Krug::Krug(const Krug& og) : Figura(og){
	r = og.r;
}

void Krug::prikazi(ostream& izlaz) const{
	Figura::prikazi(izlaz);
	izlaz << "Poluprecnik: " << r << endl;
	izlaz << endl;
}

double Krug::vratiObim() const {
	return (2 * r * 3.14);
}

double Krug::vratiPovrsinu() const{
	return ((r*r)*3.14);
}

double Krug::koeficijentFigure() const{
	return (vratiPovrsinu()/vratiObim());
}
