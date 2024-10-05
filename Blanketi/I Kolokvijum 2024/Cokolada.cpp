#include <iostream>
#include <fstream>
#include "Cokolada.h" // include za cokoladu

using namespace std;

Cokolada::Cokolada() : Poklon() // default konstruktor koji nasledjuje Poklon()
{
	procenatKakaa = 0;
}

Cokolada::Cokolada(int _cena, double _brojMasnica, int _procenatKakaa) : Poklon(_cena, _brojMasnica) // custom konstruktor koji nasledjuje Poklon(_cena, _brojMasnica)
{

	procenatKakaa = _procenatKakaa;

}

Cokolada::Cokolada(const Cokolada& og) : Poklon(og) // copy konstruktor koji nasledjuje
{
	procenatKakaa = og.procenatKakaa; // kao u osnovnoj klasi
}

void Cokolada::prikazi(ostream& izlaz) const // overirde za prikazi
{
	Poklon::prikazi(izlaz); // over se "prepisuje" iz osnovne klase
	izlaz << "Procenat kakaa: " << procenatKakaa << endl; // ovde se doradjuje za ccokoladu i njene parametre
	izlaz << endl;
}

int Cokolada::vratiBrojMasnica() const
{
	return 2 * brojMasnica; // ovo je uslov zadatka
}
