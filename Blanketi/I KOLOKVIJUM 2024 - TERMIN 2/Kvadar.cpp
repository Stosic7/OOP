#include "Kvadar.h"

Kvadar::Kvadar() : Akvarijum(){
	a = b = c = 0.0;
}

Kvadar::Kvadar(double _a, double _b, double _c, const char* _tip, bool _poklopac) : Akvarijum(_tip,_poklopac){
	a = _a;
	b = _b;
	c = _c;
}

Kvadar::Kvadar(const Kvadar& og) : Akvarijum(og){
	a = og.a;
	b = og.b;
	c = og.c;
}

void Kvadar::prikazi(ostream& izlaz) const{
	Akvarijum::prikazi(izlaz);
	izlaz << "a: " << a << "\nb: " << b << "\nc: " << c << endl;
	izlaz << endl;
}

double Kvadar::vratiPovrsinu() const{
	return (2 * ((a * b) + (a * c) + (b * c)));
}

double Kvadar::vratiZapreminu() const{
	return (a*b*c);
}

double Kvadar::koeficijentFigure() const{
	return (vratiPovrsinu() / vratiZapreminu());
}
