#include <iostream>
#include <fstream>
#include "Poklon.h" // include za header poklon

using namespace std; // kontejnerska klasa

Poklon::Poklon() // implementacija default konstruktora
{
	cena = 0; // self explanatory 
	brojMasnica = 0; // self explanatory 
}

Poklon::Poklon(double _cena, int _brojMasnica) // implementacija custom konstruktora
{

	cena = _cena; // cena uzima vrednost parametra _cena
	brojMasnica = _brojMasnica; // isto i za ovo

}

Poklon::Poklon(const Poklon& og) // -||- copy contrucotra
{

	cena = og.cena; // isti fazon ko za konstruktor (za staticke promenljive) samo uzima parametar og.
	brojMasnica = og.brojMasnica; // isto

}

Poklon :: ~Poklon() // -||- destruktora
{} // prazno, jer su sve promenljive staticke, posle cemo videti kako se implementira za dinamicke promenljive

void Poklon::prikazi(ostream& izlaz) const // -||- funckije za prikaz
{

	izlaz << "Cena: " << cena << "\nBroj masnica: " << brojMasnica << endl; //  self explanatory 

}

ostream& operator<<(ostream& izlaz, const Poklon& p) // implementacija operatora <<
{

	p.prikazi(izlaz); // poziva se prikaz kome se prosledjuje izlaz

	return izlaz; // mora da vrati izlaz

}
